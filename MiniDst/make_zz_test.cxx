//
// Created by Maurik Holtrop on 7/11/20.
//

#include "cxxopts.hpp"
#include "TChain.h"
#include "MiniDst.h"
#include "Dst2016.h"

#include "LcioReader.h"
#include <locale.h>


using namespace std;

int main(int argc, char **argv){

	cout << "Start Running Simple for Testing LCIO Infile" << endl;

	int debug_code = 0;
//	std::string infiles = "/work/hallb/hps/maurik/physrun2021/Moller_MC/HPS-v2021-1pt92GeV/moller-beam_all.slcio";
    string infiles = argv[1];
    cout << "Processing input file: " << infiles << endl;

	auto dstlcio = new LcioReader(infiles, 6);
	//if(args["magfield"].as<double>() > 0.) dstlcio->magnetic_field = args["magfield"].as<double>();
	cout << "Set ZERO BFIELD For Simplicity and Comp" << endl;

	dstlcio->magnetic_field = 0.0;

	cout << "Pass ok" << endl;
	//auto dst = static_cast<MiniDst*>(dstlcio);
    auto dst = static_cast<MiniDst*>(dstlcio);


	// Slightly "expensive", but it is really nice to know ahead of time if we need MCParticle in the DST.
	dstlcio->lcio_reader->open(infiles);
	cout << "Does that OPEN?" << endl;

	cout << "Does that OPEN -> Get ok" << endl;
	cout << "lcio_reader->getNumberOfEvents() = " << dstlcio->lcio_reader->getNumberOfEvents() << endl;
	cout << "lcio_reader->getNumberOfRuns() = " << dstlcio->lcio_reader->getNumberOfRuns() << endl;

//	auto lcio_event = dstlcio->lcio_reader->readNextEvent();
	cout << "START" << endl;
	
//	const vector<string> *col_names = lcio_event->getCollectionNames();

	cout << "START" << endl;

	dstlcio->Start();
	cout << "START -> DONE" << endl;
	cout << "process -> Begin" << endl;

	//dstlcio->Process(10);
       
	for(int i = 0; i < 100; i++){
    
		cout << "Now Processing Event: " << i << endl;
		dstlcio->Process(i);

	}


	cout << "process -> DONE" << endl;

//	if( std::find(col_names->begin(), col_names->end(), "MCParticle") != col_names->end()
//			and !no_mc_particles) dst->use_mc_particles = true;
	dstlcio->lcio_reader->close();


}
