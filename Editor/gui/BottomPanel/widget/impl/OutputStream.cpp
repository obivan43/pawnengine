#include "OutputStream.h"

#include <QString>

namespace editor {

	namespace impl {

		OutputStream::OutputStream(std::ostream& stream, QTextEdit* textEdit) : std::basic_streambuf<char>(), m_Stream(stream) {
			m_LogWindow = textEdit;
			m_OldBuffer = stream.rdbuf();

			stream.rdbuf(this);
		}

		OutputStream::~OutputStream() {
			m_Stream.rdbuf(m_OldBuffer);
		}

		void OutputStream::registerConsoleMessageHandler() {
			qInstallMessageHandler(consoleMessageHandler);
		}

		int OutputStream::overflow(int v) {
			if (v == '\n') {
				m_LogWindow->append("");
			}

			return v;
		}

		std::streamsize OutputStream::xsputn(const char* p, std::streamsize n) {
			QStringList matchList{ "[info]", "[error]", "[debug]", "[trace]", "[warning]" };
			QString str{ p };

			m_LogWindow->moveCursor(QTextCursor::End);

			if (m_LogWindow->textColor() != QColorConstants::Black) {
				m_LogWindow->setTextColor(QColorConstants::Black);
			}

			for (QString match : matchList) {
				if (str.contains(match)) {
					if (match == matchList[0]) {
						m_LogWindow->setTextColor(QColorConstants::Black);
					}

					if (match == matchList[1]) {
						m_LogWindow->setTextColor(QColorConstants::Red);
					}

					if (match == matchList[2]) {
						m_LogWindow->setTextColor(QColorConstants::LightGray);
					}

					if (match == matchList[3]) {
						m_LogWindow->setTextColor(QColorConstants::LightGray);
					}

					if (match == matchList[4]) {
						m_LogWindow->setTextColor(QColorConstants::Yellow);
					}

					break;
				}
			}

			m_LogWindow->insertPlainText(str);

			return n;
		}

		void OutputStream::consoleMessageHandler(QtMsgType type, const QMessageLogContext&, const QString& msg) {
			std::cout << msg.toStdString().c_str();
		}

	}

}
