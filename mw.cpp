#include "mw.h"
#include "viewcart.h"

MainWindow::MainWindow()
{
	// Title
	setWindowTitle("Amazon");
    ds=new store();
    // Instantiate the parser
    DBParser parser;
    success=1;
    parser.addProductParser(new ProductBookParser);
    parser.addProductParser(new ProductClothingParser);
    parser.addProductParser(new ProductMovieParser);
    bool o=parser.parse("database.txt", *ds);
		// Overall layout
	overallLayout = new QHBoxLayout();
	reviewsDisplayLayout = new QVBoxLayout();
	productDisplayLayout = new QVBoxLayout();
	userDisplayLayout = new QVBoxLayout();
	control = new QVBoxLayout();
	overallLayout->addLayout(reviewsDisplayLayout);
	overallLayout->addLayout(productDisplayLayout);
	overallLayout->addLayout(userDisplayLayout);
	overallLayout->addLayout(control);

	productListWidget = new QListWidget();
	reviewsListWidget = new QListWidget();
	userListWidget = new QListWidget();

	reviewsNameLabel = new QLabel("reviews");
	reviewsDisplayLayout->addWidget(reviewsNameLabel);
	reviewsDisplayLayout->addWidget(reviewsListWidget);
	productNameLabel = new QLabel("Product");
	productDisplayLayout->addWidget(productNameLabel);	
	alpha = new QRadioButton("list by alphabeta");
	rating = new QRadioButton("list by rating");
	alpha->setChecked(true);
	group1 = new QButtonGroup();
	group1->addButton(alpha,0);
	group1->addButton(rating,1);
	productDisplayLayout->addWidget(alpha);
	productDisplayLayout->addWidget(rating);
	productDisplayLayout->addWidget(productListWidget);
	userNameLabel = new QLabel("users");
	userDisplayLayout->addWidget(userNameLabel);
	userDisplayLayout->addWidget(userListWidget);

	words = new QLabel("Search Keywords");
	keywords = new QLineEdit();
	AND = new QRadioButton ("Search by and");
	OR = new QRadioButton ("Search by or");
	search = new QPushButton ("Search");
	addReview = new QPushButton("Add Review");
	addCart = new QPushButton("Add to Cart");
	viewCart = new QPushButton("View Cart");
	quit = new QPushButton("Save and Quit");
	q = new QPushButton("Exit");
	group = new QButtonGroup();
	group->addButton(AND,0);
	group->addButton(OR,1);
	AND->setChecked(true);
	ac = new QPushButton("Add Credit");
	userDisplayLayout->addWidget(ac);
	control->addWidget(words);
	control->addWidget(keywords);
	control->addWidget(AND);
	control->addWidget(OR);
	control->addWidget(search);
	control->addWidget(addCart);
	control->addWidget(viewCart);
	reviewsDisplayLayout->addWidget(addReview);
	control->addWidget(quit);
	control->addWidget(q);
	for (unsigned int i=0; i<ds->users.size(); i++){
		string info = ds->users[i]->getName();
		info += "\tQty: 0  Total: $0";
		userListWidget->addItem(QString::fromStdString(info));
	}

	reviewsDisplayLayout->addStretch();
	productDisplayLayout->addStretch();
	userDisplayLayout->addStretch();
	control->addStretch();
	connect(quit, SIGNAL(clicked()), this, SLOT(showQuit()));
	connect(viewCart, SIGNAL(clicked()), this, SLOT(ViewCart()));
	connect(search, SIGNAL(clicked()), this, SLOT(Search()));
	connect(productListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(displayReview()));
	overallLayout->addStretch();
	connect(addReview, SIGNAL(clicked()), this, SLOT(AddReview()));
	connect(addCart,SIGNAL(clicked()),this,SLOT(add()));
	connect(ac,SIGNAL(clicked()),this,SLOT(credit()));
	connect(group,SIGNAL(buttonClicked(int)),this,SLOT(Search()));
	connect(group1,SIGNAL(buttonClicked(int)),this,SLOT(Search()));
	connect(q,SIGNAL(clicked()),this,SLOT(exit()));
	setLayout(overallLayout);
    if (o){
    	error(3);
    	success=0;
    	return;
    }
}

MainWindow::~MainWindow(){
	delete ds;
	userListWidget->clear();
	productListWidget->clear();
	reviewsListWidget->clear();
	delete ac;
	delete group;
	delete reviewsDisplayLayout;
	delete productDisplayLayout;
	delete userDisplayLayout;
	delete control;
	delete keywords;
	delete addReview;
	delete addCart;
	delete viewCart;
	delete quit;
	delete q;
	delete AND;
	delete OR;
	delete alpha;
	delete rating;
	delete group1;
	delete search;
	delete words;
	delete productListWidget;
	delete reviewsListWidget;
	delete userListWidget;
	delete reviewsNameLabel;
	delete productNameLabel;
	delete userNameLabel;
	delete overallLayout;
}
void MainWindow::showQuit(){
	QMessageBox msgBox;
	msgBox.setWindowTitle("Quit");
	msgBox.setText("Are you sure to quit?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);
	int userAnswer = msgBox.exec();
	if(userAnswer == QMessageBox::Yes) {
		fstream o("database.txt");
		ds->dump(o);
		o.close();
		this->close();
	}
	else if(userAnswer == QMessageBox::No) {
		return;
	}
}

void MainWindow::ViewCart(){
	int row = userListWidget->currentRow();
	if (row==-1) error(1);
	else {
		viewcart* view = new viewcart(ds->users[row],this);
		view->show();
	}
}

void MainWindow::Search(){
	hits.clear();
	productListWidget->clearSelection();
	productListWidget->clearFocus();
	productListWidget->clear();
	reviewsListWidget->clear();
	string line = keywords->text().toStdString();
	if (line.empty()) return;
	stringstream ss(line);
	vector<string> terms=Keys(ss);
    hits = ds->search(terms, group->checkedId());
	sort(hits);
	for (unsigned int i=0; i<hits.size(); i++){
		string info = hits[i]->getName();
		stringstream ss;
		double price = hits[i]->getPrice();
		ss << price;
		string pri;
		ss >> pri;
		info+="   $";
		info+=pri;
		productListWidget->addItem(QString::fromStdString(info));
	}
}

void MainWindow::sort(vector<Product*>& p){
	if (group1->checkedId()==0){
		Comparator1 comp1;
		mergeSort(p,comp1,0,p.size()-1);
	}
	else{
		Comparator2 comp2(ds);
		mergeSort(p,comp2,0,p.size()-1);
	}
}

void MainWindow::displayReview(){
	reviewsListWidget->clear();
	int productIndex = productListWidget->currentRow();
	vector<Review*> r;
	for (unsigned int i=0; i<ds->reviews.size(); i++){
		if (ds->reviews[i]->prodName==hits[productIndex]->getName()) {r.push_back(ds->reviews[i]);}
	}
	Comparator3 comp3;
	mergeSort(r,comp3,0,r.size()-1);
	for (unsigned int i=0; i<r.size(); i++){
		string info,s;
		stringstream ss;
		ss << r[i]->rating;
		info = "Rating: ";
		ss >> s;
		info+=s;
		info+="\n";
		info+="Data: ";
		info+=r[i]->date;
		info+="\n";
		info+="Comment: ";
		info+=r[i]->reviewText;
		info+="\n";
		reviewsListWidget->addItem(QString::fromStdString(info));
	}
}

void MainWindow::AddReview(){
	int row = productListWidget->currentRow();
	if (row==-1) error(2);
	else {
		string prodName = hits[row]->getName();
		ar* Ar = new ar(prodName,ds);
		Ar->show();
	}
}

void MainWindow::add(){
	int userRow = userListWidget->currentRow();
	int prodRow = productListWidget->currentRow();
	if (userRow==-1){
		error(1);
	}
	else if (prodRow==-1){
		error(2);
	}
	else {
		ds->users[userRow]->addItem(hits[prodRow]);
		reset();
	}
	userListWidget->setCurrentRow(userRow);
}

void MainWindow::reset(){
	userListWidget->clear();
	for (unsigned int i=0; i<ds->users.size(); i++){
		stringstream ss;
		string info = ds->users[i]->getName();
		info += "\tQty: ";
		ss << ds->users[i]->cart_.size();
		string num;
		ss >> num;
		info+=num;
		info += "  Total: $";
		double pri=0;
		for (unsigned int j=0; j<ds->users[i]->cart_.size(); j++) pri+=ds->users[i]->cart_[j]->getPrice();
		stringstream ss1;
		ss1 << pri;
		string p;
		ss1 >> p;
		info+=p;
		userListWidget->addItem(QString::fromStdString(info));
	}
}

void MainWindow::error(int i){
	QMessageBox msgBox;
	if (i==1){
		msgBox.setWindowTitle("Warning");
		msgBox.setText("Please select a user");
	}
	else if (i==2){
		msgBox.setWindowTitle("Warning");
		msgBox.setText("Please select a product");
	}
	else if (i==3){
		msgBox.setWindowTitle("Error");
		msgBox.setText("Database could not be used");		
	}
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);
	int userAnswer = msgBox.exec();
	if(userAnswer == QMessageBox::Ok) {
		msgBox.close();
	}
}

void MainWindow::credit(){
	int row = userListWidget->currentRow();
	if (row==-1){
		error(1);
		return;
	}
	QMessageBox msgBox;
	msgBox.setWindowTitle("Add Credit");
	msgBox.setText("Do you want to add $100 to this account?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);
	int userAnswer = msgBox.exec();
	if(userAnswer == QMessageBox::Yes) {
		ds->users[row]->add(100);
		msgBox.close();
	}
	else if(userAnswer == QMessageBox::No) {
		msgBox.close();
	}
}

vector<string> MainWindow::Keys(stringstream& words){
    vector<string> keys;
    while (!words.fail()) {
        string word;
        words >> word;
        int x=0;
        for (unsigned int i=0; i<word.size(); i++) {
            if (ispunct(word[i])and(word[i]!='-')) {
                string sub=word.substr(x,i-x);
                x=i+1;
                if (sub.size()>1) keys.push_back(convToLower(sub));
            }
        }
        string sub=word.substr(x,word.size());
        if (sub.size()>1) keys.push_back(convToLower(sub));
    }
    return keys;
}

void MainWindow::exit(){
	QMessageBox msgBox;
	msgBox.setWindowTitle("Exit");
	msgBox.setText("Do you want to quit without saving data?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);
	int userAnswer = msgBox.exec();
	if(userAnswer == QMessageBox::Yes) {
		msgBox.close();
		this->close();
	}
	else if(userAnswer == QMessageBox::No) {
		msgBox.close();
	}
}