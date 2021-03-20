#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QCloseEvent>

#include "gui/BottomPanel/include/bottompanelwidget.h"
#include "gui/LeftPanel/include/leftpanelwidget.h"
#include "gui/RightPanel/include/rightpanelwidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = Q_NULLPTR);

        uint32_t GetDefaultWidth() const { return DefaultWidth; }
        uint32_t GetDefaultHeight() const { return DefaultHeight; }

        pawn::Engine* GetEngine() { return m_Engine.get(); }

		void closeEvent(QCloseEvent* event);

    private:
        void InitEngine();

    public:
        bool Running = true;

    private:
        BottomPanelWidget* m_BottomPanel;
        LeftPanelWidget* m_LeftPanel;
        RightPanelWidget* m_RightPanel;

        QFrame* m_EngineView;

		const uint32_t DefaultWidth = 1280;
		const uint32_t DefaultHeight = 720;

        std::shared_ptr<pawn::Engine> m_Engine;
};
