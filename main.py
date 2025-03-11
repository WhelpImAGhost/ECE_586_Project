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

        self.process = None  # Will hold the running process

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

        self.text_output.append(f"Starting: {program} {' '.join(args)}\n")
        self.process.start(program, args)

        if self.process.state() == QProcess.ProcessState.Running:
            self.send_button.setEnabled(True)

    def read_output(self):
        output = self.process.readAllStandardOutput().data().decode()
        self.text_output.append(f"{output}")

    def read_error(self):
        error_output = self.process.readAllStandardError().data().decode()
        self.text_output.append(f"STDERR: {error_output}")

    def send_input(self):
        input_text = self.input_line.text() + "\n"
        if self.process and self.process.state() == QProcess.ProcessState.Running:
            self.process.write(input_text.encode())
            self.process.waitForBytesWritten()

    def process_finished(self):
        self.text_output.append("Process finished.\n")
        self.send_button.setEnabled(False)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
