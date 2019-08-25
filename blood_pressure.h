#pragma once

struct blood_pressure
{
  int systolic;
  int syst_idx;
  int diastolic;
  int dias_idx;
};


struct blood_pressure* get_blood_pressure(int data[], int size, int index);

