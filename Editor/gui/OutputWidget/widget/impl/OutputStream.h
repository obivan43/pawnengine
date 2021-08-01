#pragma once

#include <iostream>
#include <QtWidgets/QTextEdit>

#include <QObject>

namespace editor {

	namespace impl {

		class OutputStream : public QObject, public std::basic_streambuf<char> {
			Q_OBJECT

			public:
				OutputStream(std::ostream& stream);

				virtual ~OutputStream();
				static void registerConsoleMessageHandler();

			signals:
				void ColorChanged(const QColor& color);
				void Append(const QString& text);
				void InsertText(const QString& text);

			protected:
				virtual int overflow(int v);
				virtual std::streamsize xsputn(const char* p, std::streamsize n);

			private:
				static void consoleMessageHandler(QtMsgType type, const QMessageLogContext&, const QString& msg);

			private:
				std::ostream& m_Stream;
				std::streambuf* m_OldBuffer;
		};

	}

}
