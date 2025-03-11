import sys
from PyQt6.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QTextEdit, QLineEdit, QLabel, QMessageBox
from PyQt6.QtCore import QProcess

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

        # Connect Enter key in program and arguments inputs to start_process
        self.program_input.returnPressed.connect(self.start_process)
        self.args_input.returnPressed.connect(self.start_process)

        # Connect Enter key in the send input field to send_input
        self.input_line.returnPressed.connect(self.send_input)

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

        # Debugging: Show that the program will start
        self.text_output.append(f"Starting program: {program} with arguments: {' '.join(args)}\n")

        self.process.start(program, args)

        if self.process.state() == QProcess.ProcessState.Running:
            self.send_button.setEnabled(True)

    def read_output(self):
        output = self.process.readAllStandardOutput().data().decode()
        if output:  # Only append if there is output
            self.text_output.append(f"{output}")
        else:
            self.text_output.append("No output received.\n")  # Debug message

    def read_error(self):
        error_output = self.process.readAllStandardError().data().decode()
        if error_output:  # Only append if there is error output
            self.text_output.append(f"Error: {error_output}")
        else:
            self.text_output.append("No error output received.\n")  # Debug message

    def send_input(self):
        input_text = self.input_line.text()
        if input_text:  # Only send if the input is not empty
            self.text_output.append(f"{input_text}")  # Show input in the output display
            self.input_line.clear()  # Clear the input field after sending

            if self.process and self.process.state() == QProcess.ProcessState.Running:
                input_text_with_newline = input_text + "\n"
                self.process.write(input_text_with_newline.encode())
                self.process.waitForBytesWritten()

    def process_finished(self):
        self.text_output.append("Process finished.\n")
        self.send_button.setEnabled(False)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
