void StandaloneApplication(int argc, char** argv) {
  // eventually, evaluate the application parameters argc, argv
  // ==>> here the ROOT macro is called
	Ex11_exampleMacro_GUI();
}
  // This is the standard "main" of C++ starting
  // a ROOT application
int main(int argc, char** argv) {
   TApplication app("ROOT Application", &argc, argv);
   StandaloneApplication(app.Argc(), app.Argv());
   app.Run();
   return 0;
}
