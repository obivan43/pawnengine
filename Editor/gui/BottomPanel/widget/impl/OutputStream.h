#pragma once

#include <iostream>
#include <QtWidgets/QTextEdit>

namespace editor {

	namespace impl {

		class OutputStream : public std::basic_streambuf<char> {

			public:
				OutputStream(std::ostream& stream, QTextEdit* textEdit);

				virtual ~OutputStream();
				static void registerConsoleMessageHandler();

			protected:
				virtual int overflow(int v);
				virtual std::streamsize xsputn(const char* p, std::streamsize n);

			private:
				static void consoleMessageHandler(QtMsgType type, const QMessageLogContext&, const QString& msg);

			private:
				std::ostream& m_Stream;
				std::streambuf* m_OldBuffer;
				QTextEdit* m_LogWindow;
		};

	}

}
