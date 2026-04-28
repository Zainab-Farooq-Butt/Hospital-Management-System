#include "Staff.h"
#include "Patient.h"
#include "Doctor.h"
#include "MedicalRecords.h"
#include "Billing.h"
#include "Room.h"

Billing::Billing() {
    billId="";
	patientId = "";
	doctorId = "";
    recordId = "";
	doctorFee = 0;
	roomFee = 0;
	treatmentCost = 0;
	totalAmount=0;
	status="";
	billDate = "1/1/2000";
}
Billing::Billing(string bID,string patID, string docID,string recID, double docfee, double roomfee, double tmentcost,string stat, string date) {  //string tment is for treatment(used like this everywhere else as well)
	billId=bID;
	patientId = patID;
	doctorId = docID;
    recordId = recID;
	doctorFee = docfee;
	roomFee = roomfee;
	treatmentCost = tmentcost;
	totalAmount=doctorFee+roomFee+treatmentCost;
	status=stat;
	billDate = date;
}
string Billing::generateBillId()const {
	billCounter++;
	string num = to_string(billCounter);
	while (num.length() < 4) {
		num = "0" + num;
	}
	string id = "B-" + num;
	return id;
}
//Validating Bill ID
bool Billing::isValidBillId(string id) {
	if (id == "")
		return false;
	int len = 0;
	for (int i = 0; id[i] != '\0'; i++) {
		len++;
	}
	if (id[0] != 'B' || id[1] != '-'|| len!=6)
		return false;
	for (int i = 2; id[i] != '\0'; i++) {
		if (isdigit(id[i])==false)
			return false;
	}
	return true;
}
bool Billing::billIdAlreadyExists(string id) {
	ifstream infile("Billing.txt");
	if (infile.is_open()) {
		string sep,bId;
		while (getline(infile, sep)) {
			getline(infile, bId);
			if (bId == id)
				return true;
			string skip;								//Skipping the rest(Only need BillID)
			for (int i = 0; i < 9; i++) {
				getline(infile, skip);
			}
		}
		infile.close();
		return false;
	}
	return false;
}
//Validating Date
bool Billing::isLeapYear(int year) const {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
bool Billing::isValidBillDate(string dt) {
	int firstSlash=dt.find('/');
	if (firstSlash == string::npos)	//npos means NOT FOUND
		return false;
	int secondSlash = dt.find('/',firstSlash+1);
	if (secondSlash == string::npos)	
		return false;
	int date = stoi(dt.substr(0,firstSlash));
	int month = stoi(dt.substr(firstSlash+1,secondSlash-firstSlash-1));
	int year = stoi(dt.substr(secondSlash+1));
	if (year < 1900 || year>2100)
		return false;
	if (month < 1 || month>12)
		return false;
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		if (date < 1 || date>31)
			return false;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (date < 1 || date>30)
			return false;
	}
	else {
		if (isLeapYear(year)) {
			if (date < 1 || date>29)
				return false;
		}
		else {
			if (date < 1 || date>28)
				return false;
		}
	} 
	return true;
}
//Getter 
string Billing::getBillId()const{
    return billId;
}
string Billing::getPatientId()const{
    return patientId;
}
string Billing::getDoctorId()const{
    return doctorId;
}
string Billing::getRecordId()const{
    return recordId;
}
double Billing::getDoctorFee()const{
    return doctorFee;
}
double Billing::getRoomFee()const{
    return roomFee;
}
double Billing::getTreatmentCost()const{
    return treatmentCost;
}
double Billing::getTotalAmount()const{
	return totalAmount;
}
string Billing::getStatus()const{
	return status;
}
string Billing::getBillDate()const{
    return billDate;
}
//Setters
void Billing::setBillId(string id){
    if (isValidBillId(id))
		billId = id;
	else
		cout << "Invalid Bill Id" << endl;
}
void Billing::setPatientId(string id){
	Patient p;
    if (p.isValidPatientId(id))
		patientId = id;
	else
		cout << "Invalid Patient Id" << endl;
}
void Billing::setDoctorId(string id){
	Doctor d;
    if (d.isValidDoctorId(id))
		doctorId = id;
	else
		cout << "Invalid Doctor Id" << endl;
}
void Billing::setRecordId(string id){
	MedicalRecords m;
    if (m.isValidRecordId(id))
		recordId = id;
	else
		cout << "Invalid Record Id" << endl;
}
void Billing::setDoctorFee(double fee){
     if (fee>=0)
		doctorFee=fee;
	else
		cout<<"Invalid Doctor Fee"<<endl;
}
void Billing::setRoomFee(double fee){
    if (fee>=0)
		roomFee=fee;
	else
		cout<<"Invalid Room Fee"<<endl;
}
void Billing::setTreatmentCost(double fee){
    if (fee>=1)
		treatmentCost=fee;
	else
		cout<<"Invalid Treatment Cost"<<endl;
}
void Billing::setTotalAmount(){
	totalAmount=treatmentCost+doctorFee+roomFee;
}
void Billing::setStatus(string stat){
	if(stat=="Paid"|| stat=="Unpaid" || stat=="Partially Paid")
		status=stat;
	else
		cout<<"Invalid Status"<<endl;
}
void Billing::setBillDate(string dt){
    if(isValidBillDate(dt))
		billDate=dt;
	else
		cout<<"Invalid Date"<<endl;
}
//Display Functions
//When calling from main call this one 1 time and then the normal display function
void Billing::displayHeader()const {
	cout << left;
	cout<< setw(10) << "BillID"<< setw(12) << "PatientID"<< setw(12) << "DoctorID"<< setw(12) << "RecordID"<< setw(12) << "DoctorFee"<< setw(10) << "RoomFee"<< setw(15) << "TreatmentCost" <<setw(12)<<"Total"<<setw(10)<<"Status"<<setw(12)<<"Date"<<endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << right;
}
//Displays 1 Record(Used as helper)
void Billing::display() const {
	cout << left;
	cout<< setw(10) << billId<< setw(12) << patientId << setw(12) << doctorId<< setw(12) << recordId<< setw(12) << doctorFee<< setw(10) << roomFee<< setw(15) << treatmentCost<<setw(12)<<totalAmount<<setw(10)<<status <<setw(12)<<billDate<<endl;
	cout<<right;
}
void Billing::displayAllBills() {
	ifstream infile("Billing.txt");
	if (!infile.is_open()) {
		cout << "Error Opening File" << endl;
		return;
	}
	string sep;
	bool empty = true;
	displayHeader();
	while (getline(infile, sep)) {
		getline(infile, billId);
		getline(infile, patientId);
		getline(infile, doctorId);
		getline(infile, recordId);
		infile>>doctorFee;
		infile>>roomFee;
		infile>>treatmentCost;
		infile>>totalAmount;
		infile.ignore();
		getline(infile, status);
		getline(infile, billDate);
		empty = false;
		display();
	}
	infile.close();
	if (empty)
		cout << "No bills found" << endl;
}
//----Managing Records-----
void Billing::setBilling(string currentUser){
	if(currentUser!="ADMIN"){
		cout<<"Access Denied"<<endl;
		return;
	}
	billId=generateBillId();
	while(true){
		cout<<"Enter Record ID (format R-0001)"<<endl;
		cin>>recordId;
		MedicalRecords m;
		if(!m.isValidRecordId(recordId))
			cout<<"Invalid Record ID.Try Again"<<endl;
		else if(!m.recordIdAlreadyExists(recordId,"MedicalRecords.txt"))
			cout<<"Record ID doesn't exist.Try Again"<<endl;
		else{
			m.fetchFromFile(recordId);
			patientId=m.getPatientId();
			doctorId=m.getDoctorId();
			treatmentCost=m.getTreatmentCost();
			break;
		}
	}
	double doctorFee = 0;
	ifstream dfile("Doctor.txt");
	string ln;
	while (getline(dfile, ln)) {
		if (ln != "----------") continue;
		Doctor d;
		d.Load_From_File(dfile);
		if (d.getDoctorId() == doctorId) {
			doctorFee = d.getConsultationFee();
			break;
		}
	}
	dfile.close();
	this->doctorFee = doctorFee;
	Room r;
	roomFee=r.fetchRoomFee(patientId);
	totalAmount=doctorFee+roomFee+treatmentCost;
	cout<<"\n--- Billing Summary ---"<<endl;
	cout<<"Bill ID: "<<billId<<endl;
	cout<<"Patient ID: "<<patientId<<endl;
	cout<<"Doctor ID: "<<doctorId<<endl;
	cout<<"Record ID: "<<recordId<<endl;
	cout<<"Doctor Fee: "<<doctorFee<<endl;
	cout<<"Treatment Cost: "<<treatmentCost<<endl;
	cout<<"Room Fee: "<<roomFee<<endl;
	cout<<"Total: "<<totalAmount<<endl;
	double amountReceived;
	cout<<"Enter Amount Received"<<endl;
	cin>>amountReceived;
	while(amountReceived<=0){
		cout<<"Invalid Amount.Try Again"<<endl;
		cin>>amountReceived;
	}
	if(amountReceived==totalAmount)
		status="Paid";
	else if(amountReceived>totalAmount){
		double change=amountReceived-totalAmount;
		cout<<"Change: "<<change<<endl;
		status="Paid";
	}
	else if(amountReceived>0 && amountReceived<totalAmount){
		status="Partially Paid";
		totalAmount=totalAmount-amountReceived;
		cout<<"Remaining Amount: "<<totalAmount<<endl;
	}
	else
		status="Unpaid";
	cin.ignore();
	cout<<"Enter Billing Date (format 1/1/2000)"<<endl;
	while(true){
		getline(cin,billDate);
		if(!isValidBillDate(billDate))
			cout<<"Invalid Date.Try Again"<<endl;
		else
			break;
	}
	saveToFile();
	cout<<"Bill Generated Succesfully"<<endl;
}
void Billing::updateStatus(string currentUser){
	if(currentUser!="ADMIN"){
		cout<<"Access Denied."<<endl;
		return;
	}
	displayAllBills();
	string bId;
	cout<<"Enter Bill ID of the bill you want to update"<<endl;
	cin>>bId;
	while(!isValidBillId(bId)){
		cout<<"Invalid Bill ID.Try Again"<<endl;
		cin>>bId;
	}
	string bIds[100],pIds[100],dIds[100],rIds[100],stats[100],dates[100];
	double roomfees[100],docfees[100],tmentcosts[100],totals[100];
	string sep;
	int count=0;
	ifstream infile("Billing.txt");
	if(!infile.is_open()){
		cout<<"Error Opening File"<<endl;
		return;
	}
	while(getline(infile,sep)){
			getline(infile, bIds[count]);
			getline(infile, pIds[count]);
			getline(infile, dIds[count]);
			getline(infile, rIds[count]);
			infile>>docfees[count];
			infile>>roomfees[count];
			infile>>tmentcosts[count];
			infile>>totals[count];
			infile.ignore();
			getline(infile, stats[count]);
			getline(infile, dates[count]);
			count++;
	}
	infile.close();
	int index=-1;
	for(int i=0;i<count;i++){
		if(bId==bIds[i]){
			index=i;
			break;
		}
	}
	if(index==-1){
		cout<<"Bill ID not found"<<endl;
		return;
	}
	double amountReceived;
	cout<<"Enter Amount Received"<<endl;
	cin>>amountReceived;
	while(amountReceived<=0){
		cout<<"Invalid Amount.Try Again"<<endl;
		cin>>amountReceived;
	}
	if(amountReceived==totals[index])
		stats[index]="Paid";
	else if(amountReceived>totals[index]){
		double change=amountReceived-totals[index];
		cout<<"Change: "<<change<<endl;
		stats[index]="Paid";
	}
	else if(amountReceived>0 && amountReceived<totals[index]){
		stats[index]="Partially Paid";
		totals[index]=totals[index]-amountReceived;
		cout<<"Remaining Amount: "<<totals[index]<<endl;
	}
	else
		stats[index]="Unpaid";
	ofstream outfile("Billing.txt");
	if(!outfile.is_open()){
		cout<<"Error Writing to file"<<endl;
		return;
	}
	for(int i=0;i<count;i++){
		outfile << "-----------" << endl;
		outfile << bIds[i] << endl;
		outfile << pIds[i] << endl;
		outfile << dIds[i] << endl;
		outfile << rIds[i] << endl;
		outfile << docfees[i] << endl;
		outfile << roomfees[i] << endl;
		outfile << tmentcosts[i] << endl;
		outfile << totals[i] << endl;
		outfile << stats[i] << endl;
		outfile << dates[i] << endl;
	}
	outfile.close();
	cout<<"Status Updated Successfully"<<endl;
}
//Search Functions
bool Billing::searchByBillId(string id) {
	bool found = false;
	ifstream infile("Billing.txt");
	if (infile.is_open()) {
		displayHeader();
		string sep,bId, pId, dId,rId,stat,dt;
		double docfee,roomfee,tmentcost,total;
		while (getline(infile, sep)) {
			getline(infile, bId);
			getline(infile, pId);
			getline(infile, dId);
			getline(infile, rId);
			infile>>docfee;
			infile>>roomfee;
			infile>>tmentcost;
			infile>>total;
			infile.ignore();
			getline(infile, stat);
			getline(infile, dt);
			if (bId == id) {
				found = true;
				cout << left;
				cout<< setw(10) << bId<< setw(12) << pId << setw(12) << dId<< setw(12) << rId<< setw(12) << docfee<< setw(10) << roomfee<< setw(15) << tmentcost<<setw(12)<<total<<setw(10)<<stat <<setw(12)<<dt<<endl;
				cout<<right;
				infile.close();
				return found;
			}
		}
		infile.close();
	}
	return found;
}
bool Billing::searchByPatientId(string id) {
	bool found = false;
	ifstream infile("Billing.txt");
	if (infile.is_open()) {
		displayHeader();
		string sep,bId, pId, dId,rId,stat,dt;
		double docfee,roomfee,tmentcost,total;
		while (getline(infile, sep)) {
			getline(infile, bId);
			getline(infile, pId);
			getline(infile, dId);
			getline(infile, rId);
			infile>>docfee;
			infile>>roomfee;
			infile>>tmentcost;
			infile>>total;
			infile.ignore();
			getline(infile, stat);
			getline(infile, dt);
			if (pId == id) {
				found = true;
				cout << left;
				cout<< setw(10) << bId<< setw(12) << pId << setw(12) << dId<< setw(12) << rId<< setw(12) << docfee<< setw(10) << roomfee<< setw(15) << tmentcost<<setw(12)<<total<<setw(10)<<stat <<setw(12)<<dt<<endl;
				cout<<right;
				infile.close();
			}
		}
		infile.close();
	}
	return found;
}
//File Handling
void Billing::loadCounterFromFile() {		//Static Function
	ifstream infile("Billing.txt");
	int maxnum = 0;
	int num = 0;
	string sep, bId;
	if (infile.is_open()) {
		while (getline(infile, sep)) {
			getline(infile, bId);
			int num = stoi(bId.substr(2));				//stoi converts string to int
			if (maxnum < num)
				maxnum = num;
			string skip;								//Skipping the rest(Only need RecordID)
			for (int i = 0; i < 9; i++) {
				getline(infile, skip);
			}
		}
		infile.close();
	}
	billCounter = maxnum;
}
void Billing::saveToFile()const {
	ofstream outfile("Billing.txt", ios::app);
	if (outfile.is_open()) {
		outfile << "-----------" << endl;
		outfile << billId << endl;
		outfile << patientId << endl;
		outfile << doctorId << endl;
		outfile << recordId << endl;
		outfile << doctorFee << endl;
		outfile << roomFee << endl;
		outfile << treatmentCost << endl;
		outfile << totalAmount << endl;
		outfile << status << endl;
		outfile << billDate << endl;
	}
}
void Billing::loadFromFile() {
	ifstream infile("Billing.txt");
	if (infile.is_open()) {
		string seperator;
		getline(infile, seperator);
		getline(infile, billId);
		getline(infile, patientId);
		getline(infile, doctorId);
		getline(infile, recordId);
		infile>>doctorFee;
		infile>>roomFee;
		infile>>treatmentCost;
		infile>>totalAmount;
		infile.ignore();
		getline(infile, status);
		getline(infile, billDate);
	}
}
Billing::~Billing(){}
int Billing::billCounter = 0;		//IMP NOTE:IN MAIN DO THIS----> Billing::loadCounterFromFile()