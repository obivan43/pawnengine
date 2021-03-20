#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QLineEdit>
#include <QCloseEvent>

#include "gui/OuputWindow/include/outputwindow.h"
#include "gui/Hierarchy/include/hierarchywindow.h"

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
        void InitInspectorPanel();

        void UpdateInspectorPanel();

    private slots:
        void OnLineEditPress();
        void OnSelectedEntityChanged(pawn::Entity entity);

    public:
        bool Running = true;

    private:
        OutputWindow* m_OutputWindow;
        HierarchyWindow* m_HierarchyWindow;

        QTreeWidgetItem* m_Tag;
        QTreeWidgetItem* m_TagChild;
        QLineEdit* entityLineEdit;
        QTreeWidgetItem* m_Transformation;
        QLineEdit* m_EntityNameLineEdit;
		QTreeWidget* m_Inspector;
		QDockWidget* m_InspectorDockWidget;

        QFrame* m_EngineView;

		const uint32_t DefaultWidth = 1280;
		const uint32_t DefaultHeight = 720;

        pawn::Entity m_SelectedEntity;

        std::shared_ptr<pawn::Engine> m_Engine;
};
