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
	remainingAmount=0;
	status="";
	billDate = "1/1/2000";
}
Billing::Billing(string bID,string patID, string docID,string recID, double docfee, double roomfee, double tmentcost,double remaining,string stat, string date) {  //string tment is for treatment(used like this everywhere else as well)
	billId=bID;
	patientId = patID;
	doctorId = docID;
    recordId = recID;
	doctorFee = docfee;
	roomFee = roomfee;
	treatmentCost = tmentcost;
	totalAmount=doctorFee+roomFee+treatmentCost;
	remainingAmount=remaining;
	status=stat;
	billDate = date;
}
string Billing::generateBillId() {
    billCounter++;
    string num = to_string(billCounter);
    while (num.length() < 4) {
        num = "0" + num;
    }

    return "B-" + num;
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
			for (int i = 0; i < 10; i++) {
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
double Billing::getRemainingAmount() const {
    return remainingAmount;
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
void Billing::setRemainingAmount(double amount) {
    if(amount >= 0)
        remainingAmount = amount;
    else
        cout << "Invalid Remaining Amount" << endl;
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
void Billing::displayHeader() const {
    cout << left;
    cout << setw(10) << "BillID"
         << setw(20) << "Patient"
         << setw(20) << "Doctor"
         << setw(12) << "RecordID"
         << setw(12) << "DoctorFee"
         << setw(10) << "RoomFee"
         << setw(15) << "TreatmentCost"
         << setw(12) << "Total"
		 << setw(12) << "Remaining"
         << setw(15) << "Status"
         << setw(12) << "Date" << endl;
    cout << string(150, '-') << endl;  // auto-fills dashes to match width
    cout << right;
}
//Displays 1 Record(Used as helper)
void Billing::display() const {
    Patient p;
    Doctor d;
    cout << left;
    cout << setw(10) << billId
         << setw(20) << p.getNameById(patientId)
         << setw(20) << d.getNameById(doctorId)
         << setw(12) << recordId
         << setw(12) << doctorFee
         << setw(10) << roomFee
         << setw(15) << treatmentCost
         << setw(12) << totalAmount
		 << setw(12) << remainingAmount
         << setw(15) << status
         << setw(12) << billDate << endl;
    cout << right;
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
		infile>>remainingAmount;
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
void Billing::setBilling(string currentUser,string pid){
	if(currentUser!="ADMIN"){
		cout<<"Access Denied"<<endl;
		return;
	}

	cout<<"Enter Record ID (format R-0001)"<<endl;
	cin>>recordId;
	while(true){
		MedicalRecords m;
		if(!m.isValidRecordId(recordId)){
			cout<<"Invalid Record ID. Try Again."<<endl;
			cin>>recordId;
		}
		else if(!m.recordIdAlreadyExists(recordId)){
			cout<<"Record ID doesn't exist"<<endl;
			return;
		}
		else{
			m.fetchFromFile(recordId);
			patientId=pid;
			doctorId=m.getDoctorId();
			treatmentCost=m.getTreatmentCost();
			break;
		}
	}
	if(!Patient_has_RID(patientId,recordId)){
		cout<<patientId<<" has no "<<recordId<<endl;
		return;
	}
	// if(billExistsForThisRecord(recordId)){
	// 	cout<<"A bill already exists for this record"<<endl;
	// 	return;
	// }
	billId=generateBillId();
	Doctor d;
	doctorFee=d.fetchDoctorFee(doctorId,"Doctor.txt");
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
	if(amountReceived==totalAmount){
		status="Paid";
		remainingAmount=0;
	}
	else if(amountReceived>totalAmount){
		double change=amountReceived-totalAmount;
		cout<<"Change: "<<change<<endl;
		status="Paid";
		remainingAmount=0;
	}
	else if(amountReceived>0 && amountReceived<totalAmount){
		status="Partially Paid";
		remainingAmount=totalAmount-amountReceived;
		cout<<"Remaining Amount: "<<remainingAmount<<endl;
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
void Billing::updateStatus(string currentUser,string pId){
	if(currentUser!="ADMIN"){
		cout<<"Access Denied."<<endl;
		return;
	}
	if(!searchByPatientId(pId)){
		return;
	}
	string bId;
	cout<<"Enter Bill ID of the bill you want to update"<<endl;
	cin>>bId;
	while(!isValidBillId(bId)){
    	cout<<"Invalid Bill ID format.Try Again"<<endl;
    	cin>>bId;
	}
	if(!billIdAlreadyExists(bId)){
    	cout<<"Bill ID doesn't exist."<<endl;
    	return;
	}
	if(!Patient_has_BID(pId,bId)){
		cout<<pId<<" has no "<<bId<<endl;
		return;
	}


	string bIds[100],pIds[100],dIds[100],rIds[100],stats[100],dates[100];
	double roomfees[100],docfees[100],tmentcosts[100],totals[100],ramounts[100];
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
			infile>>ramounts[count];
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
	if(stats[index]=="Paid"){
		cout<<"Bill is already paid.Cannot update"<<endl;
		return;
	}
	double amountReceived;
	cout<<"Enter Amount Received"<<endl;
	cin>>amountReceived;
	while(amountReceived<=0){
		cout<<"Invalid Amount.Try Again"<<endl;
		cin>>amountReceived;
	}
	if(amountReceived >= ramounts[index]){
    	double change = amountReceived - ramounts[index];
    	if(change > 0) 
			cout << "Change: " << change << endl;
    	stats[index] = "Paid";
    	ramounts[index] = 0;
	}
	else if(amountReceived > 0 && amountReceived < ramounts[index]){
    stats[index] = "Partially Paid";
    ramounts[index] = ramounts[index] - amountReceived;
    cout << "Remaining Amount: " << ramounts[index] << endl;
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
		outfile << ramounts[i]<<endl;
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
		string sep,bId, pId, dId,rId,stat,dt;
		double docfee,roomfee,tmentcost,total,ramount;
		while (getline(infile, sep)) {
			getline(infile, bId);
			getline(infile, pId);
			getline(infile, dId);
			getline(infile, rId);
			infile>>docfee;
			infile>>roomfee;
			infile>>tmentcost;
			infile>>total;
			infile>>ramount;
			infile.ignore();
			getline(infile, stat);
			getline(infile, dt);
			if (bId == id) {
    			found = true;
    			billId=bId,patientId=pId,doctorId=dId,recordId=rId,
				doctorFee=docfee,roomFee=roomfee,treatmentCost=tmentcost,
				totalAmount=total,remainingAmount=ramount,status=stat,billDate=dt;
    			display(); 
    			infile.close();
   				return found;
			}
		}
		infile.close();
	}
	if(!found){
		cout<<"No bill found"<<endl;
	}
	return found;
}
bool Billing::searchByPatientId(string id) {
	bool found = false;
	ifstream infile("Billing.txt");
	if (infile.is_open()) {
		string sep,bId, pId, dId,rId,stat,dt;
		double docfee,roomfee,tmentcost,total,ramount;
		while (getline(infile, sep)) {
			getline(infile, bId);
			getline(infile, pId);
			getline(infile, dId);
			getline(infile, rId);
			infile>>docfee;
			infile>>roomfee;
			infile>>tmentcost;
			infile>>total;
			infile>>ramount;
			infile.ignore();
			getline(infile, stat);
			getline(infile, dt);
			if (pId == id) {
				found = true;
    			billId=bId,patientId=pId,doctorId=dId,recordId=rId,
				doctorFee=docfee,roomFee=roomfee,treatmentCost=tmentcost,
				totalAmount=total,remainingAmount=ramount,status=stat,billDate=dt;
    			display();
			}
		}
		if (found==false){
			cout<<"No Bills for Patient ID: "<< id<<endl;
		}
		infile.close();
	}
	return found;
}
void Billing::displayAllPatientBills() {
    ifstream infile("Patient.txt");
    if (!infile.is_open()) {
        cout << "Error opening Patient.txt" << endl;
        return;
    }

    string line, cnic, pid, blood, type, contact, status;
    double height, weight;
    bool anyFound = false;

    displayHeader();  // print header once at the top

    while (getline(infile, line)) {
        if (line != "----------") 
			continue;

        getline(infile, cnic);      // CNIC
        getline(infile, pid);       // Patient ID
        getline(infile, blood);     // blood group
        getline(infile, type);      // patient type
        infile >> height;           // height
        infile >> weight;           // weight
        infile.ignore(1000, '\n');
        getline(infile, contact);   // emergency contact
        getline(infile, status);    // status

        if (pid != "") {
            bool found = searchByPatientId(pid);
            if (found) anyFound = true;
        }
    }
    infile.close();

    if (!anyFound)
        cout << "No bills found for any patient." << endl;
}
//File Handling
void Billing::loadCounterFromFile(string filename) {
    ifstream infile(filename);
    int maxnum = 0;
    string line, bId;

    if (infile.is_open()) {
        while (getline(infile, line)) {

            // Check separator
            if (line == "-----------") {

                // Next line is Bill ID
                getline(infile, bId);

                if (bId.length() >= 3) {
                    int num = stoi(bId.substr(2)); // skip "B-"
                    if (num > maxnum)
                        maxnum = num;
                }

                // Skip remaining 10 lines of record
                string skip;
                for (int i = 0; i < 10; i++) {
                    getline(infile, skip);
                }
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
		outfile << remainingAmount<<endl;
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
		infile>>remainingAmount;
		infile.ignore();
		getline(infile, status);
		getline(infile, billDate);
	}
}

bool Billing::Patient_has_RID(string patientid,string recordid){
	ifstream infile("MedicalRecords.txt",ios::in);
	string extra,pid,rid;
	double extra2;
	while(!infile.eof()){
		getline(infile,extra);
		getline(infile,rid);
		getline(infile,pid);
		getline(infile,extra);
		getline(infile,extra);
		getline(infile,extra);
		infile>>extra2;
		infile.ignore();
		getline(infile,extra);

		if (pid==patientid){
			if(rid==recordid){
				return true;
			}
		}
	}
	return false;
}

bool Billing::billExistsForThisRecord(string recId){
	ifstream infile("Billing.txt");
	if(!infile.is_open()){
		cout<<"Error Opening File"<<endl;
		return false;
	}
	string sep,bId,dId,pId,rId,stat,d;
	double dfee,rfee,tcost,total,ramount;
	while(getline(infile,sep)){
		getline(infile,bId);
		getline(infile,pId);
		getline(infile,dId);
		getline(infile,rId);
		infile>>dfee>>rfee>>tcost>>total>>ramount;
		infile.ignore();
		getline(infile,stat);
		getline(infile,d);
		if(rId==recId){
			infile.close();
			return true;
		}
	}
	infile.close();
	return false;
}

bool Billing::Patient_has_BID(string patientid,string billid){
	ifstream infile("Billing.txt",ios::in);
	string extra,pid,bid;
	double extra2;
	while(!infile.eof()){
		getline(infile,extra);
		getline(infile,bid);
		getline(infile,pid);
		getline(infile,extra);
		getline(infile,extra);
		infile>>extra2;
		infile>>extra2;
		infile>>extra2;
		infile>>extra2;
		infile>>extra2;
		infile.ignore();
		getline(infile,extra);
		getline(infile,extra);

		if (pid==patientid){
			if(bid==billid){
				return true;
			}
		}
	}
	return false;
}











Billing::~Billing(){};
int Billing::billCounter = 0;		