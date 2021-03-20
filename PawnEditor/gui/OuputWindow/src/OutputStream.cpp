#include "pch.h"
#include "OutputStream.h"

namespace impl {

	OutputStream::OutputStream(std::ostream& stream, QTextEdit* text_edit) : std::basic_streambuf<char>() , m_stream(stream) {
		log_window = text_edit;
		m_old_buf = stream.rdbuf();

		stream.rdbuf(this);
	}

	OutputStream::~OutputStream() {
		m_stream.rdbuf(m_old_buf);
	}

	void OutputStream::registerConsoleMessageHandler() {
		qInstallMessageHandler(consoleMessageHandler);
	}

	int OutputStream::overflow(int v) {
		if (v == '\n') {
			log_window->append("");
		}

		return v;
	}

	std::streamsize OutputStream::xsputn(const char* p, std::streamsize n) {
		QString str(p);

		log_window->moveCursor(QTextCursor::End);
		log_window->insertPlainText(str);

		return n;
	}

	void OutputStream::consoleMessageHandler(QtMsgType type, const QMessageLogContext&, const QString& msg) {
		std::cout << msg.toStdString().c_str();
	}

}
