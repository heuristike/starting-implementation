#include "std.h"
#include<string>
#include<iostream>
#include<cstdio>

using namespace std;

//Konstruktor
STD::STD(){
	strcpy(name, "");
	jobs=0;
	solution=-1; //nema poznatog b&b rješenja
	ptv='';
	tf='';
	ddr='';
	process_time=NULL;
	due_date=NULL;
	setup_times=NULL;
}

//Destruktor
STD::~STD(){
	if( process_time!=NULL ) delete[] process_time;
	if( due_date!=NULL ) delete[] due_date;
	if( setup_times!=NULL ) delete[] setup_times;

	process_time=NULL;
	due_date=NULL;
	setup_times=NULL;
}

//Copy-konstruktor (JE LI DOBRO?)
STD::STD( const STD& problem ){
	jobs = problem.jobs;
	name = problem.name;
	solution = problem.solution;
	ptv = problem.ptv;
	tf = problem.tf;
	ddr = problem.ddr;

	delete[] process_time;
	delete[] due_date;
	delete[] setup_times;

	process_time = new int[problem.jobs]; // duljina polja koji sadrži processing times je n (broj poslova-jobs)
	due_date = new int[problem.jobs];
	setup_times = new int[problem.jobs+1][problem.jobs];
			
	for ( int i=0; i<=jobs; ++i ) {
		if( i!=jobs ){
			process_time[i]=problem.process_time[i];
			due_date[i]=problem.due_date[i];
		}

		for ( int j=0; j<jobs; ++j ){
			setup_times[i][j]=problem.setup_times[i][j];
		}
			
	}
}

//Operator pridruživanja (=)
STD& STD::operator=( const STD& problem ){
	if( this->name!=problem.name ){ //Pridružujemo samo kada su problemi zaista različiti 
		//ime datoteke u kojoj se nalazi problem je različit od imena datoteke u kojoj se nalazi problem 'problem'
		
		jobs = problem.jobs;
		name = problem.name;
		solution = problem.solution;
		ptv = problem.ptv;
		tf = problem.tf;
		ddr = problem.ddr;
		
		delete[] process_time;
		delete[] due_date;
		delete[] setup_times;

		process_time = new int[problem.jobs]; // duljina polja koji sadrži processing times je n (broj poslova-jobs)
		due_date = new int[problem.jobs];
		setup_times = new int[problem.jobs+1][problem.jobs];
		
		for ( int i=0; i<=jobs; ++i ) {
			if( i!=jobs ){
				process_time[i]=problem.process_time[i];
				due_date[i]=problem.due_date[i];
			}

			for ( int j=0; j<jobs; ++j ){
				setup_times[i][j]=problem.setup_times[i][j];
			}
			
		}

	}
	return *this;	
}

//Operatori uspoređivanja
bool STD::operator==( const STD& problem ){
	for ( int i=0; i<=jobs; ++i ) {

			if( i!=jobs ){
				if( process_time[i]!=problem.process_time[i] ) return false;
				if( due_date[i]!=problem.due_date[i] ) return false;
			}
			for ( int j=0; j<jobs; ++j ) if( setup_times[i][j]!=problem.setup_times[i][j] ) return false;
		
		}
	return true;
}

bool STD::operator!=( const STD& problem ){
	for ( int i=0; i<=jobs; ++i ) {

			if( i!=jobs ){
				if( process_time[i]!=problem.process_time[i] ) return true;
				if( due_date[i]!=problem.due_date[i] ) return true;
			}
			for ( int j=0; j<jobs; ++j ) if( setup_times[i][j]!=problem.setup_times[i][j] ) return true;
		
		}
	return false;
}


//Učitavanje nekog problema iz datoteke s imenom 'file'
bool STD::LoadProblem( char* file ){

	ifstream in_file;
	in_file.open(file);
	if( !in_file ) throw runtime_error("Can't load file!");

	//Učitaj prvu liniju iz datoteke - br.poslova, rješenje b&b, (G)ime problema=filename, (G)karakteristike problema = tri znaka 
	in_file >> jobs >> solution >> solution;
	if( jobs>=55 ) in_file >> name >> ptv >> tf >> ddr;

	int i,j;
	process_time = new int[jobs];
	due_date = new int[jobs];
	setup_times = new int[jobs+1][jobs];

	//Učitavamo processing_time
	for( i=0; i<jobs; i++ ) in_file >> process_time[i];
	//Učitavamo due_dates
	for( i=0; i<jobs; i++ ) in_file >> due_dates[i];
	//Učitavamo sve setup_times
	for( i=0; i<=jobs; i++ ){
		for( j=0; j<jobs; j++ ) in_file >> setup_times[i][j];
	}

	in_file.close();
}
