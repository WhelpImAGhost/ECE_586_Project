import sys
from PyQt6.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QTextEdit, QLineEdit
from PyQt6.QtCore import QProcess

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("PyQt and C Stdio")
        self.resize(400, 300)

        self.layout = QVBoxLayout(self)
        
        self.text_output = QTextEdit(self)
        self.text_output.setReadOnly(True)
        self.layout.addWidget(self.text_output)

        self.input_line = QLineEdit(self)
        self.layout.addWidget(self.input_line)

        self.send_button = QPushButton("Send Input", self)
        self.layout.addWidget(self.send_button)
        self.send_button.clicked.connect(self.send_input)

        self.process = QProcess(self)
        self.process.readyReadStandardOutput.connect(self.read_output)
        self.process.start("./main", ["-f","Mem_files/Float_mem/fmax.mem", "-m", "2"])
    def read_output(self):
        output = self.process.readAllStandardOutput().data().decode()
        self.text_output.append(output)

    def send_input(self):
        input_text = self.input_line.text() + "\n"
        self.process.write(input_text.encode())
        self.process.waitForBytesWritten()

app = QApplication(sys.argv)
window = MainWindow()
window.show()
sys.exit(app.exec())

