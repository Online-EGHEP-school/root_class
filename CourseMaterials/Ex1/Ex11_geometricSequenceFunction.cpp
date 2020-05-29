void  first_function(){
   double x = .5;
   int N = 30;
   double gs = 0;
   for (int i=0;i<N;++i) gs += pow(x,i);
   auto diff = std::abs(gs - (1/(1-x)));
   std::cout << "The difference is in the first function: " << diff << std::endl;
}


void  second_function(){
   double x = .5;
   int N = 30;
   double gs = 0;
   for (int i=0;i<N;++i) gs += pow(x,i);
   auto diff = std::abs(gs - (1/(1-x)));
   std::cout << "The difference is in the second function: " << diff << std::endl;
}

