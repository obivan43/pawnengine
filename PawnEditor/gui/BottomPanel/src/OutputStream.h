#pragma once

#include <iostream>
#include <QtWidgets/QTextEdit>

namespace impl {

	class OutputStream : public std::basic_streambuf<char> {

		public:
			OutputStream(std::ostream& stream, QTextEdit* text_edit);

			virtual ~OutputStream();
			static void registerConsoleMessageHandler();

		protected:
			virtual int overflow(int v);
			virtual std::streamsize xsputn(const char* p, std::streamsize n);

		private:
			static void consoleMessageHandler(QtMsgType type, const QMessageLogContext&, const QString& msg);

		private:
			std::ostream& m_stream;
			std::streambuf* m_old_buf;
			QTextEdit* log_window;
	};

}