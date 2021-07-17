#pragma once

#include <QAbstractNativeEventFilter>

namespace impl {

	class WindowsEventFilter : public QAbstractNativeEventFilter {

		public:

			WindowsEventFilter() = default;
			bool nativeEventFilter(const QByteArray& eventType, void* message, qintptr* result) override;
	};

}
