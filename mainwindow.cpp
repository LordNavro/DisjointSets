#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QXmlStreamReader>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowTitle(tr("Disjoint sets"));
    setGeometry(QRect(10,10,800,600));

    currentFileName = "";

    scene = new DisjointSetsScene(this, new QList<Node *>, DisjointSetsScene::TREE);
    connect(scene, SIGNAL(signalNodeClicked(Node*)), this, SLOT(slotNodeClicked(Node*)));
    view = new QGraphicsView(scene, this);
    view->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->setCentralWidget(view);

    createActions();
    createMenus();
    createToolBars();
    createTools();

    this->currentTool = NULL;
    this->currentSimulation = NULL;
    actionAddNode->trigger();
    actionTree->trigger();
    optimizeFindSet = false;
    optimizeUnion = false;
    actionOptimizeFindSet->trigger();
    actionOptimizeUnion->trigger();

    actionGroupSimulation->setDisabled(true);
    updateSimulationLabel();
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
    actionGroupFile = new QActionGroup(this);

    actionNew = new QAction(tr("&New"), actionGroupFile);
    actionNew->setShortcuts(QKeySequence::New);
    actionNew->setStatusTip(tr("Create new disjoint sets"));
    connect(actionNew, SIGNAL(triggered()), this, SLOT(slotNew()));

    actionSave = new QAction(tr("&Save"), actionGroupFile);
    actionSave->setShortcuts(QKeySequence::Save);
    actionSave->setStatusTip(tr("Save current disjoint sets"));
    connect(actionSave, SIGNAL(triggered()), this, SLOT(slotSave()));

    actionSaveAs = new QAction(tr("Save &As"), actionGroupFile);
    actionSaveAs->setShortcuts(QKeySequence::Save);
    actionSaveAs->setStatusTip(tr("Save current disjoint sets as a new file"));
    connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(slotSaveAs()));

    actionOpen = new QAction(tr("&Open"), actionGroupFile);
    actionOpen->setShortcuts(QKeySequence::Open);
    actionOpen->setStatusTip(tr("Open saved disjoint sets"));
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(slotOpen()));

    actionAbout = new QAction(tr("&About"), this);
    actionAbout->setShortcuts(QKeySequence::Open);
    actionAbout->setStatusTip(tr("Basic application description"));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(slotAbout()));

    actionGroupOperation = new QActionGroup(this);

    actionMakeSet = new QAction(tr("&Make set"), actionGroupOperation);
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

    actionGroupOptimalization = new QActionGroup(this);
    actionGroupOptimalization->setExclusive(false);

    actionOptimizeUnion = new QAction(tr("Optimize &Union"), actionGroupOptimalization);
    actionOptimizeUnion->setStatusTip(tr("Optimize union operation by connecting shorter/smaller list/set to higher/larger"));
    actionOptimizeUnion->setCheckable(true);
    connect(actionOptimizeUnion, SIGNAL(triggered()), this, SLOT(slotOptimizeUnion()));

    actionOptimizeFindSet = new QAction(tr("Optimize &Find Set"), actionGroupOptimalization);
    actionOptimizeFindSet->setStatusTip(tr("Optimize Find Set operation by contracting paths"));
    actionOptimizeFindSet->setCheckable(true);
    connect(actionOptimizeFindSet, SIGNAL(triggered()), this, SLOT(slotOptimizeFindSet()));

    actionGroupSimulation = new QActionGroup(this);

    actionSimulationNext = new QAction(tr("&Next step"), actionGroupSimulation);
    actionSimulationNext->setStatusTip(tr("Executes next step of the simulation"));
    connect(actionSimulationNext, SIGNAL(triggered()), this, SLOT(slotSimulationNext()));

    actionSimulationPrevious = new QAction(tr("&Previous step"), actionGroupSimulation);
    actionSimulationPrevious->setStatusTip(tr("Undoes last step of the simulation"));
    connect(actionSimulationPrevious, SIGNAL(triggered()), this, SLOT(slotSimulationPrevious()));

    actionSimulationStop = new QAction(tr("&Stop"), actionGroupSimulation);
    actionSimulationStop->setStatusTip(tr("Abandon the simulation"));
    connect(actionSimulationStop, SIGNAL(triggered()), this, SLOT(slotSimulationStop()));

    actionSimulationFinish = new QAction(tr("&Finish"), actionGroupSimulation);
    actionSimulationFinish->setStatusTip(tr("Runs the editor in state after operation"));
    connect(actionSimulationFinish, SIGNAL(triggered()), this, SLOT(slotSimulationFinish()));
}

void MainWindow::createMenus(void)
{
    menuFile = menuBar()->addMenu(tr("&File"));
    menuFile->addAction(actionNew);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionSaveAs);
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

    menuSimulation = menuBar()->addMenu("&Simulation");
    menuSimulation->addAction(actionSimulationNext);
    menuSimulation->addAction(actionSimulationPrevious);
    menuSimulation->addAction(actionSimulationStop);
    menuSimulation->addAction(actionSimulationFinish);

    menuAbout = menuBar()->addMenu(tr("&About"));
    menuAbout->addAction(actionAbout);
}

void MainWindow::createToolBars(void)
{
    toolBarFile = addToolBar(tr("File"));
    toolBarFile->addAction(actionNew);
    toolBarFile->addAction(actionSave);
    toolBarFile->addAction(actionSaveAs);
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
    toolBarRepresentation->addAction(actionTree);
    toolBarRepresentation->addAction(actionList);
    toolBarRepresentation->addAction(actionOptimizeFindSet);
    toolBarRepresentation->addAction(actionOptimizeUnion);
    addToolBar(Qt::LeftToolBarArea, toolBarRepresentation);

    labelSimulationProgress = new QLabel(this);
    labelSimulationProgress->setAlignment(Qt::AlignCenter);
    toolBarSimulation = addToolBar(tr("Simulation"));
    toolBarSimulation->addAction(actionSimulationNext);
    toolBarSimulation->addAction(actionSimulationPrevious);
    toolBarSimulation->addAction(actionSimulationStop);
    toolBarSimulation->addAction(actionSimulationFinish);
    toolBarSimulation->addWidget(labelSimulationProgress);
    addToolBar(Qt::LeftToolBarArea, toolBarSimulation);
}

void MainWindow::createTools(void)
{
    toolAddNode = new AddNodeTool(scene);
    connect(toolAddNode, SIGNAL(signalSimulate(Simulation*)), this, SLOT(slotSimulate(Simulation*)));

    toolDeleteNode = new DeleteNodeTool(scene);
    connect(toolDeleteNode, SIGNAL(signalSimulate(Simulation*)), this, SLOT(slotSimulate(Simulation*)));

    toolFindSet = new FindSetTool(scene);
    connect(toolFindSet, SIGNAL(signalSimulate(Simulation*)), this, SLOT(slotSimulate(Simulation*)));

    toolUnion = new UnionTool(scene);
    connect(toolUnion, SIGNAL(signalSimulate(Simulation*)), this, SLOT(slotSimulate(Simulation*)));
}

void MainWindow::slotNew(void)
{
    Utils::deleteForest(this->scene->forest);
    this->scene->forest = new QList<Node *>;
    this->scene->resetScene();
}

void MainWindow::slotSave(void)
{
    if(currentFileName == "")
    {
        slotSaveAs();
        return;
    }
    QFile file(currentFileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        currentFileName = "";
        QMessageBox mbox;
        mbox.setText("Cant open file " + currentFileName + "in write mode!");
        mbox.exec();
        return;
    }
    QTextStream ts(&file);

    ts << Utils::forestToXml(* scene->forest).toString();
    file.close();
    QMessageBox mbox;
    mbox.setText("Current document saved as " + currentFileName + " succesfully.");
    mbox.exec();

}

void MainWindow::slotSaveAs(void)
{
    currentFileName = QFileDialog::getSaveFileName(this, tr("Save as..."), "", tr("XML file (*.xml)"));
    if(currentFileName != "")
        slotSave();
}

void MainWindow::slotOpen(void)
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("XML File (*.xml)"));

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen())
    {
        QMessageBox::warning(this, "Open file error", "Failed to open file " + fileName);
        return;
    }

    QDomDocument xml("mydocument");
    xml.setContent(file.readAll());
    currentTool->deselectTool();
    scene->forest = Utils::xmlToForest(xml);
    scene->resetScene();
    currentTool->selectTool();
}

void MainWindow::slotAbout(void)
{
    QMessageBox::information(this, "Disjoint sets", "Simple application for simulation of disjoint sets operations. \n2012, xnavra23@fit.vutbr.cz");
}

void MainWindow::slotMakeSet(void)
{
    static int counter = 0;
    scene->forest->append(new Node(NULL, "r" + QString::number(counter++)));
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
    //the value is BEFORE CHANGE!
    optimizeFindSet = !optimizeFindSet;
    toolFindSet->optimize = optimizeFindSet;
}

void MainWindow::slotOptimizeUnion()
{
    //the value is BEFORE CHANGE!
    optimizeUnion = !optimizeUnion;
    toolUnion->optimize = optimizeUnion;
}

void MainWindow::slotSimulate(Simulation *simulation)
{
    this->currentSimulation = simulation;
    this->actionGroupFile->setDisabled(true);
    this->actionGroupOperation->setDisabled(true);
    this->actionGroupOptimalization->setDisabled(true);
    this->actionGroupRepresentation->setDisabled(true);

    this->actionGroupSimulation->setDisabled(false);

    this->view->setScene(* this->currentSimulation->currentScene);
    updateSimulationLabel();
    this->view->update();
}

void MainWindow::slotSimulationNext()
{
    this->currentSimulation->currentScene++;
    if(this->currentSimulation->currentScene == this->currentSimulation->scenes.end())
        this->currentSimulation->currentScene--;
    updateSimulationLabel();
    this->view->setScene(* this->currentSimulation->currentScene);
}

void MainWindow::slotSimulationPrevious()
{
    if(this->currentSimulation->currentScene != this->currentSimulation->scenes.begin())
        this->currentSimulation->currentScene--;
    updateSimulationLabel();
    this->view->setScene(* this->currentSimulation->currentScene);
}

void MainWindow::slotSimulationStop()
{
    this->view->setScene(this->scene);
    this->scene->resetScene();
    this->view->update();

    this->actionGroupFile->setDisabled(false);
    this->actionGroupOperation->setDisabled(false);
    this->actionGroupOptimalization->setDisabled(false);
    this->actionGroupRepresentation->setDisabled(false);

    this->actionGroupSimulation->setDisabled(true);

    delete this->currentSimulation;
    this->currentSimulation = NULL;
    updateSimulationLabel();
}


void MainWindow::slotSimulationFinish()
{

    this->view->setScene(this->scene);
    Utils::deleteForest(this->scene->forest);
    this->scene->forest = Utils::copyForest(this->currentSimulation->finalForest);
    this->scene->resetScene();
    this->view->update();

    this->actionGroupFile->setDisabled(false);
    this->actionGroupOperation->setDisabled(false);
    this->actionGroupOptimalization->setDisabled(false);
    this->actionGroupRepresentation->setDisabled(false);

    this->actionGroupSimulation->setDisabled(true);

    delete this->currentSimulation;
    this->currentSimulation = NULL;
    updateSimulationLabel();
}

void MainWindow::updateSimulationLabel(void)
{
    if(currentSimulation == NULL)
    {
        labelSimulationProgress->setText("No simulation \n in progress");
        return;
    }
    QString label = (*currentSimulation->currentScene)->label;
    int sumScenes = currentSimulation->scenes.size();
    int currentScene = currentSimulation->scenes.indexOf(*currentSimulation->currentScene) + 1;
    labelSimulationProgress->setText(QString::number(currentScene) + "/" + QString::number(sumScenes)
                                     + "\n" + label);
    actionSimulationPrevious->setDisabled(currentSimulation->currentScene == currentSimulation->scenes.begin());
    actionSimulationNext->setDisabled(currentSimulation->currentScene + 1 == currentSimulation->scenes.end());

}
