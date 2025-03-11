import sys
import ctypes
import platform
from PyQt6.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QTextEdit, QLineEdit, QLabel, QMessageBox
from PyQt6.QtCore import QThread, pyqtSignal, QProcess

def load_shared_library():
    current_platform = platform.system().lower()

    if current_platform == "windows":
        return ctypes.CDLL("./main.dll")
    elif current_platform == "linux":
        return ctypes.CDLL("./main.so")
    elif current_platform == "darwin":
        return ctypes.CDLL("./main.dylib")
    else:
        raise Exception(f"Unsupported platform: {current_platform}")

class VariableUpdateThread(QThread):
    # Define custom signals to send updated values back to the main thread
    mode_signal = pyqtSignal(int)
    breakpoints_signal = pyqtSignal(int)
    watching_signal = pyqtSignal(int)
    step_signal = pyqtSignal(int)

    def __init__(self, shared_lib):
        super().__init__()
        self.shared_lib = shared_lib
        self.running = True

    def run(self):
        while self.running:
            try:
                # Read values from the C shared library
                mode_value = self.shared_lib.get_mode()
                breakpoints_value = self.shared_lib.get_breakpoints()
                watching_value = self.shared_lib.get_watching()
                step_value = self.shared_lib.get_step()

                # Debugging output
                print(f"Updating: Mode={mode_value}, Breakpoints={breakpoints_value}, Watching={watching_value}, Step={step_value}")

                # Emit signals with the updated values
                self.mode_signal.emit(mode_value)
                self.breakpoints_signal.emit(breakpoints_value)
                self.watching_signal.emit(watching_value)
                self.step_signal.emit(step_value)

                # Sleep for a second before reading again
                self.msleep(1000)  # Sleep for 1 second
            except Exception as e:
                print(f"Error reading variables: {e}")

    def stop(self):
        self.running = False
        self.wait()


class MainWindow(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("PyQt Runtime Arguments")
        self.resize(900, 750)

        self.layout = QVBoxLayout(self)

        # Input for program name
        self.program_label = QLabel("Program:", self)
        self.layout.addWidget(self.program_label)
        self.program_input = QLineEdit(self)
        self.layout.addWidget(self.program_input)

        # Input for arguments
        self.args_label = QLabel("Arguments:", self)
        self.layout.addWidget(self.args_label)
        self.args_input = QLineEdit(self)
        self.layout.addWidget(self.args_input)

        # Button to start process
        self.start_button = QPushButton("Start Program", self)
        self.layout.addWidget(self.start_button)
        self.start_button.clicked.connect(self.start_process)

        # Output display
        self.text_output = QTextEdit(self)
        self.text_output.setReadOnly(True)
        self.layout.addWidget(self.text_output)

        # Input field for sending data to the program
        self.input_line = QLineEdit(self)
        self.layout.addWidget(self.input_line)

        self.send_button = QPushButton("Send Input", self)
        self.layout.addWidget(self.send_button)
        self.send_button.clicked.connect(self.send_input)
        self.send_button.setEnabled(False)  # Disabled until process starts

        self.process = None

        # Load the shared library
        try:
            self.shared_lib = load_shared_library()
            self.text_output.append("Shared library loaded successfully.")

            # Set function return types
            self.shared_lib.get_mode.restype = ctypes.c_int
            self.shared_lib.get_breakpoints.restype = ctypes.c_int
            self.shared_lib.get_watching.restype = ctypes.c_int
            self.shared_lib.get_step.restype = ctypes.c_int

            # Labels to display the C variable values
            self.mode_label = QLabel("Mode: 0", self)
            self.layout.addWidget(self.mode_label)

            self.breakpoints_label = QLabel("Breakpoints: 0", self)
            self.layout.addWidget(self.breakpoints_label)

            self.watching_label = QLabel("Watching: 0", self)
            self.layout.addWidget(self.watching_label)

            self.step_label = QLabel("Step: 0", self)
            self.layout.addWidget(self.step_label)

            # Start the worker thread for updating variables
            self.update_thread = VariableUpdateThread(self.shared_lib)

            # Connect the signals to update the UI
            self.update_thread.mode_signal.connect(self.update_mode)
            self.update_thread.breakpoints_signal.connect(self.update_breakpoints)
            self.update_thread.watching_signal.connect(self.update_watching)
            self.update_thread.step_signal.connect(self.update_step)

            self.update_thread.start()

        except Exception as e:
            self.text_output.append(f"Error loading shared library: {e}")

        # Connect Enter key in program and arguments inputs to start_process
        self.program_input.returnPressed.connect(self.start_process)
        self.args_input.returnPressed.connect(self.start_process)

        # Connect Enter key in the send input field to send_input
        self.input_line.returnPressed.connect(self.send_input)

    def update_mode(self, mode_value):
        """Update the mode label in the GUI."""
        print(f"Update Mode: {mode_value}")  # Debugging output
        self.mode_label.setText(f"Mode: {mode_value}")

    def update_breakpoints(self, breakpoints_value):
        """Update the breakpoints label in the GUI."""
        print(f"Update Breakpoints: {breakpoints_value}")  # Debugging output
        self.breakpoints_label.setText(f"Breakpoints: {breakpoints_value}")

    def update_watching(self, watching_value):
        """Update the watching label in the GUI."""
        print(f"Update Watching: {watching_value}")  # Debugging output
        self.watching_label.setText(f"Watching: {watching_value}")

    def update_step(self, step_value):
        """Update the step label in the GUI."""
        print(f"Update Step: {step_value}")  # Debugging output
        self.step_label.setText(f"Step: {step_value}")

    def start_process(self):
        self.text_output.clear()
        program = self.program_input.text().strip()
        args = self.args_input.text().strip().split()  # Split by spaces

        if not program:
            QMessageBox.warning(self, "Error", "Please enter a program name.")
            return

        self.process = QProcess(self)
        self.process.readyReadStandardOutput.connect(self.read_output)
        self.process.readyReadStandardError.connect(self.read_error)
        self.process.finished.connect(self.process_finished)

        self.text_output.append(f"Starting program: {program} with arguments: {' '.join(args)}\n")

        self.process.start(program, args)

        if self.process.state() == QProcess.ProcessState.Running:
            self.send_button.setEnabled(True)

    def read_output(self):
        output = self.process.readAllStandardOutput().data().decode()
        if output:
            self.text_output.append(output)

    def read_error(self):
        error_output = self.process.readAllStandardError().data().decode()
        if error_output:
            self.text_output.append(f"Error: {error_output}")

    def send_input(self):
        input_text = self.input_line.text()
        if input_text:
            self.text_output.append(f"Input: {input_text}")
            self.input_line.clear()

            if self.process and self.process.state() == QProcess.ProcessState.Running:
                self.process.write((input_text + "\n").encode())
                self.process.waitForBytesWritten()

    def process_finished(self):
        self.text_output.append("Process finished.\n")
        self.send_button.setEnabled(False)

    def closeEvent(self, event):
        """Stop the update thread when the window is closed."""
        self.update_thread.stop()
        super().closeEvent(event)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
