#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowTitle(tr("Disjoint sets"));

    forest = new QList<Node *>;

    createActions();
    createMenus();
    createToolBars();
    createTools();


    QBrush brush(Qt::green);
    QPen pen(Qt::yellow);
    scene = new DisjointSetsScene(this, forest, DisjointSetsScene::TREE, pen, brush, pen);
    connect(scene, SIGNAL(signalNodeClicked(Node*)), this, SLOT(slotNodeClicked(Node*)));
    view = new QGraphicsView(scene, this);
    this->setCentralWidget(view);

    this->currentTool = NULL;
    actionAddNode->trigger();
    actionList->trigger();

    //THIS FUCKING DEFAULT LINE NEARLY RUINED WHOLE PROJECT
    //ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    //fixme: delete forest and its items
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::createActions(void)
{
    actionNew = new QAction(tr("&New"), this);
    actionNew->setShortcuts(QKeySequence::New);
    actionNew->setStatusTip(tr("Create new disjoint sets"));
    connect(actionNew, SIGNAL(triggered()), this, SLOT(slotNew()));

    actionSave= new QAction(tr("&Save"), this);
    actionSave->setShortcuts(QKeySequence::Save);
    actionSave->setStatusTip(tr("Save current disjoint sets"));
    connect(actionSave, SIGNAL(triggered()), this, SLOT(slotSave()));

    actionOpen = new QAction(tr("&Open"), this);
    actionOpen->setShortcuts(QKeySequence::Open);
    actionOpen->setStatusTip(tr("Open saved disjoint sets"));
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(slotOpen()));

    actionAbout = new QAction(tr("&About"), this);
    actionAbout->setShortcuts(QKeySequence::Open);
    actionAbout->setStatusTip(tr("Basic application description"));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(slotAbout()));

    actionGroupOperation = new QActionGroup(this);

    actionMakeSet = new QAction(tr("&Make set"), this);
    actionMakeSet->setStatusTip(tr("Make new set"));
    connect(actionMakeSet, SIGNAL(triggered()), this, SLOT(slotMakeSet()));

    actionFindSet = new QAction(tr("&Find set"), actionGroupOperation);
    actionFindSet->setStatusTip(tr("Find representative"));
    actionFindSet->setCheckable(true);
    connect(actionFindSet, SIGNAL(triggered()), this, SLOT(slotFindSet()));

    actionUnion = new QAction(tr("&Union"), actionGroupOperation);
    actionUnion->setStatusTip(tr("Union two sets"));
    actionUnion->setCheckable(true);
    connect(actionUnion, SIGNAL(triggered()), this, SLOT(slotUnion()));

    actionAddNode = new QAction(tr("&Add node"), actionGroupOperation);
    actionAddNode->setStatusTip(tr("Edit graph adding nodes"));
    actionAddNode->setCheckable(true);
    connect(actionAddNode, SIGNAL(triggered()), this, SLOT(slotAddNode()));

    actionDeleteNode = new QAction(tr("&Delete node"), actionGroupOperation);
    actionDeleteNode->setStatusTip(tr("Edit graph adding nodes"));
    actionDeleteNode->setCheckable(true);
    connect(actionDeleteNode, SIGNAL(triggered()), this, SLOT(slotDeleteNode()));

    actionGroupRepresentation = new QActionGroup(this);

    actionTree = new QAction(tr("&Tree representation"), actionGroupRepresentation);
    actionTree->setStatusTip(tr("Represent set items as a tree"));
    actionTree->setCheckable(true);
    connect(actionTree, SIGNAL(triggered()), this, SLOT(slotTree()));

    actionList = new QAction(tr("&List representation"), actionGroupRepresentation);
    actionList->setStatusTip(tr("Represent set items as a list"));
    actionList->setCheckable(true);
    connect(actionList, SIGNAL(triggered()), this, SLOT(slotList()));

    actionOptimizeUnion = new QAction(tr("Optimize &Union"), this);
    actionOptimizeUnion->setStatusTip(tr("Optimize union operation by connecting shorter/smaller list/set to higher/larger"));
    actionOptimizeUnion->setCheckable(true);
    connect(actionOptimizeUnion, SIGNAL(triggered()), this, SLOT(slotOptimizeUnion()));

    actionOptimizeFindSet = new QAction(tr("Optimize &Find Set"), this);
    actionOptimizeFindSet->setStatusTip(tr("Optimize Find Set operation by contracting paths"));
    actionOptimizeFindSet->setCheckable(true);
    connect(actionOptimizeFindSet, SIGNAL(triggered()), this, SLOT(slotOptimizeFindSet()));
}

void MainWindow::createMenus(void)
{
    menuFile = menuBar()->addMenu(tr("&File"));
    menuFile->addAction(actionNew);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionOpen);

    menuTool = menuBar()->addMenu("&Tool");
    menuTool->addAction(actionMakeSet);
    menuTool->addAction(actionFindSet);
    menuTool->addAction(actionUnion);
    menuTool->addAction(actionAddNode);
    menuTool->addAction(actionDeleteNode);

    menuRepresentation = menuBar()->addMenu("&Representation");
    menuRepresentation->addAction(actionTree);
    menuRepresentation->addAction(actionList);
    menuRepresentation->addAction(actionOptimizeUnion);
    menuRepresentation->addAction(actionOptimizeFindSet);

    menuAbout = menuBar()->addMenu(tr("&About"));
    menuAbout->addAction(actionAbout);
}

void MainWindow::createToolBars(void)
{
    toolBarFile = addToolBar(tr("File"));
    toolBarFile->addAction(actionNew);
    toolBarFile->addAction(actionSave);
    toolBarFile->addAction(actionOpen);
    toolBarFile->setAllowedAreas(Qt::TopToolBarArea | Qt::LeftToolBarArea);
    addToolBar(Qt::TopToolBarArea, toolBarFile);

    toolBarOperation = addToolBar(tr("Operation"));
    toolBarOperation->addAction(actionMakeSet);
    toolBarOperation->addAction(actionFindSet);
    toolBarOperation->addAction(actionUnion);
    toolBarOperation->addAction(actionAddNode);
    toolBarOperation->addAction(actionDeleteNode);
    toolBarOperation->setAllowedAreas(Qt::TopToolBarArea | Qt::LeftToolBarArea);
    addToolBar(Qt::TopToolBarArea, toolBarOperation);

    toolBarRepresentation = addToolBar(tr("Representation"));
    toolBarRepresentation->addAction(actionList);
    toolBarRepresentation->addAction(actionTree);
    toolBarRepresentation->addAction(actionOptimizeFindSet);
    toolBarRepresentation->addAction(actionOptimizeUnion);
}

void MainWindow::createTools(void)
{
    toolAddNode = new AddNodeTool(scene);

    toolDeleteNode = new DeleteNodeTool(scene);

    toolFindSet = new FindSetTool(scene);

    toolUnion = new UnionTool(scene);
}

void MainWindow::slotNew(void)
{

}

void MainWindow::slotSave(void)
{

}

void MainWindow::slotOpen(void)
{

}

void MainWindow::slotAbout(void)
{

}

void MainWindow::slotMakeSet(void)
{
    forest->append(new Node(NULL, "new root node"));
    scene->resetScene();
}

void MainWindow::slotFindSet(void)
{
    if(currentTool != NULL)
        currentTool->deselectTool();
    currentTool = toolFindSet;
    currentTool->selectTool();
}

void MainWindow::slotUnion(void)
{
    if(currentTool != NULL)
        currentTool->deselectTool();
    currentTool = toolUnion;
    currentTool->selectTool();
}

void MainWindow::slotAddNode(void)
{
    if(currentTool != NULL)
        currentTool->deselectTool();
    currentTool = toolAddNode;
    currentTool->selectTool();
}

void MainWindow::slotDeleteNode(void)
{
    if(currentTool != NULL)
        currentTool->deselectTool();
    currentTool = toolDeleteNode;
    currentTool->selectTool();
}

void MainWindow::slotNodeClicked(Node *node)
{
    currentTool->nodeClicked(node);
}


void MainWindow::slotList()
{
    currentTool->deselectTool();
    scene->representation = DisjointSetsScene::LIST;
    scene->resetScene();
    currentTool->selectTool();
}

void MainWindow::slotTree()
{
    currentTool->deselectTool();
    scene->representation = DisjointSetsScene::TREE;
    scene->resetScene();
    currentTool->selectTool();
}

void MainWindow::slotOptimizeFindSet()
{
    optimizeFindSet = actionFindSet->isChecked();
}

void MainWindow::slotOptimizeUnion()
{
    optimizeUnion = actionUnion->isChecked();
}


