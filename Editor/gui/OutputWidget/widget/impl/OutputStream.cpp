#include "OutputStream.h"

#include <QString>

namespace editor::impl {

	OutputStream::OutputStream(std::ostream& stream) : std::basic_streambuf<char>(), m_Stream(stream) {
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
			emit Append("");
		}

		return v;
	}

	std::streamsize OutputStream::xsputn(const char* p, std::streamsize n) {
		QStringList matchList{ "[info]", "[error]", "[debug]", "[trace]", "[warning]" };
		QString str{ p };

		bool changed = false;
		for (QString match : matchList) {
			if (str.contains(match)) {
				if (match == matchList[0]) {
					emit ColorChanged(QColorConstants::Black);
				}

				if (match == matchList[1]) {
					emit ColorChanged(QColorConstants::Red);
				}

				if (match == matchList[2]) {
					emit ColorChanged(QColorConstants::LightGray);
				}

				if (match == matchList[3]) {
					emit ColorChanged(QColorConstants::LightGray);
				}

				if (match == matchList[4]) {
					emit ColorChanged(QColorConstants::Yellow);
				}

				changed = true;

				break;
			}
		}

		if (!changed) {
			emit ColorChanged(QColorConstants::Black);
		}

		emit InsertText(str);

		return n;
	}

	void OutputStream::consoleMessageHandler(QtMsgType type, const QMessageLogContext&, const QString& msg) {
		std::cout << msg.toStdString().c_str();
	}

}
