#include "pch.h"
#include "OutputStream.h"

#include <QString>

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
		QStringList matchList{ "[info]", "[error]", "[debug]", "[trace]", "[warning]" };
		QString str{ p };

		log_window->moveCursor(QTextCursor::End);

		if (log_window->textColor() != QColorConstants::White) {
			log_window->setTextColor(QColorConstants::White);
		}

		for (QString match : matchList) {
			if (str.contains(match)) {
				if (match == matchList[0]) {
					log_window->setTextColor(QColorConstants::White);
				}

				if (match == matchList[1]) {
					log_window->setTextColor(QColorConstants::Red);
				}

				if (match == matchList[2]) {
					log_window->setTextColor(QColorConstants::LightGray);
				}

				if (match == matchList[3]) {
					log_window->setTextColor(QColorConstants::LightGray);
				}

				if (match == matchList[4]) {
					log_window->setTextColor(QColorConstants::Yellow);
				}

				break;
			}
		}

		log_window->insertPlainText(str);
		
		return n;
	}

	void OutputStream::consoleMessageHandler(QtMsgType type, const QMessageLogContext&, const QString& msg) {
		std::cout << msg.toStdString().c_str();
	}

}
