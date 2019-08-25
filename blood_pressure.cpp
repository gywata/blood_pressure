#include "blood_pressure.h"
#include <string>
#include <vector>

using namespace std;

struct point {
  char state; //up or down
  int index;
  int value;
  string type;
};

vector<struct point*> points;

void mark_points(int data[], int size)
{
  char state = 'i';
  bool change_state = false;
  struct point* p;

  for (int i = 0; i < size - 1; i++)
  {
    if (data[i] < data[i + 1]) {
      change_state = state == 'u' ? false : true;

      if (change_state)
      {
	state = 'u';
	p = new point;
	p->state = 'u';
	p->index = i;
	p->value = data[i];
	points.push_back(p);
      }
    }
    else if (data[i] > data[i + 1])
    {
      change_state = state == 'd' ? false : true;

      if (change_state)
      {
	state = 'd';
	p = new point;
	p->state = 'd';
	p->index = i;
	p->value = data[i];
	points.push_back(p);
      }
    }
  }   
}

void classify_points()
{
  for (int i = 0; i < points.size() - 2; i++)
  {
    if (points[i]->type != "") continue; //point already classified

    if (points[i]->state == 'u')
    {
      if (points[i]->value < points[i + 2]->value)
      {
	points[i]->type = "diastolic";
	points[i + 2]->type = "notch";
      }
      else
      {
	points[i]->type = "notch";
	points[i + 2]->type = "diastolic";
      }
    }

    if (points[i]->state == 'd')
    {
      if (points[i]->value > points[i + 2]->value)
      {
	points[i]->type = "systolic";
	points[i + 2]->type = "notch";
      }
      else
      {
	points[i]->type = "notch";
	points[i + 2]->type = "systolic";
      }
    }
  }
}

struct blood_pressure* find_points(int data[], int index)
{
  int right_value = 0;
  int left_value = 0;;
  int index_1 = 0;

  for (int i = 0; i < points.size(); i++)
  {
    if (points[i]->index >= index && points[i]->type != "notch")
    {
      right_value = points[i]->value;
      index_1 = i;
      break;
    }
  }

  for (int i = index_1 - 1; i >= 0; i--)
  {
    if (points[i]->type != "notch")
    {
      left_value = points[i]->value;
      break;
    }
  }

  int value_1 = 0;
  int idx_1 = 0;
  int value_2 = 0;
  int idx_2 = 0;
  bool found = false;

  for (int i = index; ; i++)
  {
    if (data[i] == right_value)
    {
      value_1 = data[i];
      idx_1 = i;
      found = true;
      break;
    }
  }

  if (!found) return NULL;

  found = false;

  for (int i = index; ; i--)
  {
    if (data[i] == left_value)
    {
      value_2 = data[i];
      idx_2 = i;
      found = true;
      break;
    }
  }

  if (!found) return NULL;

  struct blood_pressure* bp;

  if (value_1 > value_2)
  {
    bp->systolic = value_1;
    bp->syst_idx = idx_1;
    bp->diastolic = value_2;
    bp->dias_idx = idx_2;
  }
  else
  {
    bp->systolic = value_2;
    bp->syst_idx = idx_2;
    bp->diastolic = value_1;
    bp->dias_idx = idx_1;
  }

  return bp;
}

struct blood_pressure* get_blood_pressure(int data[], int size, int index)
{
  struct blood_pressure* bp;

  mark_points(data, size);
  classify_points();
  bp = find_points(data, index);

  for (auto p : points)
    delete p;

  points.clear();

  return bp;
}
