// ---------------------------------------------------------------------
//
// Copyright (C) 2004 - 2016 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE at
// the top level of the deal.II distribution.
//
// ---------------------------------------------------------------------



// check Vector<std::complex<double> >::lp_norm(3)

#include "../tests.h"
#include <deal.II/lac/vector.h>
#include <fstream>
#include <iomanip>
#include <vector>


void test (Vector<std::complex<double> > &v)
{
  // set some elements of the vector
  std::complex<double> sum = 0;
  for (unsigned int i=0; i<v.size(); i+=1+i)
    {
      v(i) = std::complex<double> (i+1., i+2.);
      sum += std::pow (std::abs(std::complex<double> (i+1., i+2.)),
                       3);
    }
  v.compress ();

  // then check the norm
  AssertThrow (std::abs(v.lp_norm(3) - std::pow(sum, 1./3.)) <
               1e-14*std::abs(std::pow(sum, 1./3.)),
               ExcInternalError());

  deallog << "OK" << std::endl;
}



int main ()
{
  std::ofstream logfile("output");
  deallog.attach(logfile);
  deallog.threshold_double(1.e-10);

  try
    {
      Vector<std::complex<double> > v (100);
      test (v);
    }
  catch (std::exception &exc)
    {
      deallog << std::endl << std::endl
              << "----------------------------------------------------"
              << std::endl;
      deallog << "Exception on processing: " << std::endl
              << exc.what() << std::endl
              << "Aborting!" << std::endl
              << "----------------------------------------------------"
              << std::endl;

      return 1;
    }
  catch (...)
    {
      deallog << std::endl << std::endl
              << "----------------------------------------------------"
              << std::endl;
      deallog << "Unknown exception!" << std::endl
              << "Aborting!" << std::endl
              << "----------------------------------------------------"
              << std::endl;
      return 1;
    };
}
