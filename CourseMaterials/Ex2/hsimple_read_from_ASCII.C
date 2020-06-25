{
   gROOT->Reset();
   //create a new root file to save the tuple
   TFile *fnew = new TFile("hsimple_new.root", "New");

   // the function fopen is used to establish a file pointer to read ( hence "r") the file ntuple.dat:-
   FILE *fp = fopen("hsimple.dat","r");
   //set of Float_t and Int_t variables a TNtuple object is created
   Float_t x,y,z;
   Int_t ncols;
   Int_t nlines = 0;
   //create a constructor supplied with a name, a title, and variables list which contains colon separated names
   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","x:y:z");
   //a while loop that run forever for filling
   while(1) {
	  //The function fscanf is passed the file pointer and is told to decode 3 floats:-
      ncols = fscanf(fp,"%f %f %f",&x, &y, &z);
      //If fscanf returns less than zero then it means that the EOF has been reached and so the break statement is used to escape from the while loop:
      if (ncols < 0) break;
      //If not the TNuple object is asked to Fill itself with the data read from the file:-
      ntuple->Fill(x,y,z);
      nlines++;
   }
   cout << " found " << nlines << " points" << endl ;
   fclose(fp);
   //Once the file read in full the n-tuple is asked to print itself-
   ntuple->Print();
   //Finally comes a very powerful command to draw itself:-
   //ntuple->Draw("z : sqrt(x*x + y*y)");
   ntuple->Draw("x", "y<z");

   fnew->Write();
   fnew->Close();
}
