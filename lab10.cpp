#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

//------------------------------------------------------------------
// Initialize vector with random values
//------------------------------------------------------------------
vector<int> create_random_data(int count, int range)
{     
   // Error checking
   if (count < 1) count = 1;
   if (range < 1) range = 1;

   // Insert count random values between 0..range-1 into vector
   srandom(1);
   vector<int> data(count);
   for (int index = 0; index < count; index++)
      data[index] = random() % range;
   return data;
}

//------------------------------------------------------------------
// Initialize vector with sorted values
//------------------------------------------------------------------
vector<int> create_sorted_data(int count, bool ascending)
{
   // Error checking
   if (count < 1) count = 1;

   // Insert sorted values into vector
   vector<int> data(count);
   for (int index = 0; index < count; index++)
   {
      if (ascending)
         data[index] = index;
      else
         data[index] = count-index;
   }
   return data;
}

//------------------------------------------------------------------
// Initialize vector with mostly sorted values
//------------------------------------------------------------------
vector<int> create_mostly_sorted_data(int count, int swaps)
{
   // Error checking
   if (count < 1) count = 1;

   // Create vector of sorted values
   vector<int> data = create_sorted_data(count, true);

   // Unsort vector by swapping random pairs of values
   srandom(1);
   for (int index = 0; index < swaps; index++)
   {
      int pos1 = random() % count;
      int pos2 = random() % count;
      int temp = data[pos1];
      data[pos1] = data[pos2];
      data[pos2] = temp;
   }
   return data;
}

//------------------------------------------------------------------
// Print vector to screen
//------------------------------------------------------------------
void print_data(const vector<int> &data)
{
   // Print the data
   for (int i = 0; i < (int)data.size(); i++)
   {
      if (i % 20 == 0)
         cout << endl;
      cout << data[i] << " ";
   }
   cout << endl;
}

//-----------------------------------------------------------------
// Basic bubble sort algorithm
//-----------------------------------------------------------------
void basic_bubble_sort(vector<int> &data)
{
   // Error checking
   if (data.empty()) return;

   // Loop over entire vector
   int low = 0;
   int high = (int)data.size()-1;
   for (int loop = low; loop < high; loop++)
   {
      // Loop over unsorted part of vector
      for (int index = low; index < high; index++)
      {
         // Swap two data values if out of order
         if (data[index] > data[index + 1])
         {
            int temp = data[index];
            data[index] = data[index + 1];
            data[index + 1] = temp;
         }
      }
   }
}


//-----------------------------------------------------------------
// Faster bubble sort algorithm
//------------------------------------------------------------------
void faster_bubble_sort(vector<int> &data)
{
   // Error checking
   if (data.empty()) return;

   // Loop over entire vector
   int low = 0;
   int high = (int)data.size()-1;
   bool sorted = false;
   for (int loop = low; loop < high; loop++)
   {
      // Loop over unsorted part of vector
      sorted = true;
      for (int index = low; index < high-loop; index++)
      {
         // Swap two data values if out of order
         if (data[index] > data[index + 1])
         {
            int temp = data[index];
            data[index] = data[index + 1];
            data[index + 1] = temp;
            sorted = false;
         }
      }

      // Stop looping when vector is sorted
      if (sorted) return;
   }
}

//---------------------------------------------------------------
// Selection sort algorithm
//---------------------------------------------------------------
void selection_sort(vector<int> &data)
{
   // Error checking
   if (data.empty()) return;

   // Loop over entire vector
   int low = 0;
   int high = (int)data.size()-1;
   for (int first = low; first < high; first++)
   {
      // Find index of smallest value in unsorted vector
      int smallest = first;
      for (int index = first + 1; index <= high; index++)
         if (data[index] < data[smallest])
            smallest = index;

      // Swap with first element in unsorted vector
      int temp = data[first];
      data[first] = data[smallest];
      data[smallest] = temp;
   }
}



int main()
{
    int count;
    cout << "Enter N: ";
    if (!(cin >> count) || count < 1)
    {
        cerr << "N must be a positive integer." << endl;
        return 1;
    }

    vector<int> random_data = create_random_data(count, count);
    vector<int> mostly_sorted_data = create_mostly_sorted_data(count, count / 10);
    vector<int> ascending_data = create_sorted_data(count, true);
    vector<int> descending_data = create_sorted_data(count, false);

    const char *case_names[] = {
        "random", "mostly sorted", "ascending", "descending"
    };
    const vector<int> *inputs[] = {
        &random_data, &mostly_sorted_data, &ascending_data, &descending_data
    };
    const char *algorithm_names[] = {
        "basic_bubble_sort", "faster_bubble_sort", "selection_sort"
    };

    for (int algorithm = 0; algorithm < 3; algorithm++)
    {
        cout << "\n" << algorithm_names[algorithm] << ":\n";
        for (int test_case = 0; test_case < 4; test_case++)
        {
            vector<int> data = *inputs[test_case];
            clock_t time1 = clock();
            if (algorithm == 0)
                basic_bubble_sort(data);
            else if (algorithm == 1)
                faster_bubble_sort(data);
            else
                selection_sort(data);
            clock_t time2 = clock();
            double run_time = (time2 - time1) / (double)CLOCKS_PER_SEC;
            cout << "  " << case_names[test_case] << ": "
                 << run_time << " seconds\n";
        }
    }
    return 0;
}