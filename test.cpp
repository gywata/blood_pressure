#include <iostream>
#include "blood_pressure.h"

using namespace std;

int main(){

  int data[] = {80, 80, 80, 80, 80, 80, 80, 81, 81, 85, 92, 100, 106, 116, 119, 119, 119, 117, 115, 110,
		107, 107, 107, 108, 107, 105, 100, 99, 97, 93, 92, 90, 87, 86, 84, 83, 83, 82, 82, 82,
		82, 81, 81, 81, 81, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 85, 92,
		106, 112, 116, 119, 119, 119, 117, 112, 110, 107, 107, 108, 108, 105, 102, 100, 97, 95, 93, 90,
		89, 87, 84, 84, 83, 83, 82, 82, 82, 81, 81, 81, 81, 81, 80, 80, 80, 80, 80, 80, 80};

  
  struct blood_pressure* bp = get_blood_pressure(data, 100, 10);

  cout << "Systolic: " << bp->systolic << endl;
  cout << "Systolic index: " << bp->syst_idx << endl;
  cout << "Diastolic: " << bp->diastolic << endl;
  cout << "Diastolic index: " << bp->dias_idx << endl;

  return 0;
}
