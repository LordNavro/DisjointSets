#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "tool.h"
#include "deletenodetool.h"
#include "addnodetool.h"
#include "findsettool.h"
#include "uniontool.h"
#include "node.h"
#include "nodeitem.h"
#include "disjointsetsscene.h"
#include <QFile>
#include <QMessageBox>
#include "utils.h"
#include <QFileDialog>
#include <QTextStream>
#include <QLabel>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


protected:
    void changeEvent(QEvent *e);


    Tool *currentTool;
    Simulation *currentSimulation;
    bool optimizeFindSet;
    bool optimizeUnion;

    AddNodeTool *toolAddNode;
    DeleteNodeTool *toolDeleteNode;
    FindSetTool *toolFindSet;
    UnionTool *toolUnion;

    QString currentFileName;

    void createActions(void);
    void createMenus(void);
    void createToolBars(void);
    void createTools(void);

    QPoint addNodeItemToScene(Node *node, QPoint startCoords);

    QActionGroup *actionGroupFile;
    QActionGroup *actionGroupOperation;
    QActionGroup *actionGroupRepresentation;
    QActionGroup *actionGroupOptimalization;
    QActionGroup *actionGroupSimulation;

    QAction *actionNew;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionOpen;
    QAction *actionAbout;
    QAction *actionMakeSet;
    QAction *actionFindSet;
    QAction *actionUnion;
    QAction *actionAddNode;
    QAction *actionDeleteNode;
    QAction *actionTree;
    QAction *actionList;
    QAction *actionOptimizeFindSet;
    QAction *actionOptimizeUnion;
    QAction *actionSimulationNext;
    QAction *actionSimulationPrevious;
    QAction *actionSimulationStop;
    QAction *actionSimulationFinish;

    QMenu *menuFile;
    QMenu *menuTool;
    QMenu *menuRepresentation;
    QMenu *menuSimulation;
    QMenu *menuAbout;

    QToolBar *toolBarFile;
    QToolBar *toolBarOperation;
    QToolBar *toolBarRepresentation;
    QToolBar *toolBarSimulation;

    QLabel *labelSimulationProgress;

    DisjointSetsScene *scene;
    QGraphicsView *view;

    void updateSimulationLabel(void);

public slots:
    void slotNew(void);
    void slotSave(void);
    void slotSaveAs(void);
    void slotOpen(void);
    void slotAbout(void);

    void slotMakeSet(void);
    void slotFindSet(void);
    void slotUnion(void);
    void slotAddNode(void);
    void slotDeleteNode(void);

    void slotTree(void);
    void slotList(void);
    void slotOptimizeFindSet(void);
    void slotOptimizeUnion(void);

    void slotSimulationNext(void);
    void slotSimulationPrevious(void);
    void slotSimulationStop(void);
    void slotSimulationFinish(void);

    void slotNodeClicked(Node *node);

    void slotSimulate(Simulation *);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
