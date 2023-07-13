#include <iostream>
#include <limits>
#include "BigInt/include/operators/arithmetic_assignment.hpp"
#include "BigInt/include/operators/io_stream.hpp"

using namespace std;
typedef BigInt big;
typedef string str;

const int LOWER_LIMIT_OF_MIN_SECTION_SIZE = 0;

void Query(str desiredSizeName) {
    cout << "Please enter the " << desiredSizeName << " pixel size as an integer: ";
    return;
}

template<typename T>
void CatchActions(const T& e) {
    cerr << e;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return;
}
  
void PixelSizeControl(big& desiredSize) {
    
    while(true) {
        try {
            long long test;
            if(cin >> desiredSize) {
                if(desiredSize > LOWER_LIMIT_OF_MIN_SECTION_SIZE) {
                    break;
                } else {
                    throw "Please enter an integer greater than 0: ";
                }
            } else {
                throw "Please enter a valid value: ";
            }
        } catch(const char* e) {
            CatchActions(e);
        }
    }
    return;
}

void GetMainPixelSize(big& desiredSize) {
    PixelSizeControl(desiredSize);
    return;
}

void GetMinSectionPixelSize(big& valueToCompare, big& desiredMinSize, str desiredMinSizeName) {
    Query(desiredMinSizeName);
    while(true) {
        try{
            PixelSizeControl(desiredMinSize);
            if (desiredMinSize <= valueToCompare) {
                break;
            } else {
                throw "Please enter a value less than or equal to " + desiredMinSizeName + ": ";
            }
        } catch(const str& e) {
            CatchActions(e);
        }
    }
    return;
}

// k and t are minimum values
big CalcPossibleSectionNumForkxt(big mainWidthParam, big mainHeightParam, big k, big t) {

    big aCons = mainWidthParam - k;
    big bCons = mainHeightParam - t;

    return (aCons + 1) * (aCons + 2) * (bCons + 1) * (bCons + 2) / 4;

    /*
    formula: (width - minWidth + 1) * (width - minWidth + 2) * (height - minHeight + 1) * (height - minHeight + 1) / 4
    */
}

// Parameter order for the following 3 methods: main width, main height, min width, min height
// Please use this order for correct result.
// The values for main width / minimum width and main height / minimum height are in the order you wrote while getting input, using the classic size order (width x height).

big CalcPossibleSectionNumForMinWidthxMinHeight(big mainWidthParam, big mainHeightParam, big minWidthParam, big minHeightParam) {  // These values order (minWidthParam, minHeightParam) are checked while getting the input, so there is no need for an additional control system.
    return CalcPossibleSectionNumForkxt(mainWidthParam, mainHeightParam, minWidthParam, minHeightParam);  // k parameter equals to minWidthParam, and t parameter equals to minHeightParam
}

big CalcPossibleSectionNumForMinHeightxMinWidth(big mainWidthParam, big mainHeightParam, big minWidthParam, big minHeightParam) {  // After the values are swapped, an additional control system is needed.
    if((minWidthParam < minHeightParam && minHeightParam > mainWidthParam) || (minHeightParam < minWidthParam && minWidthParam > mainHeightParam)) {  // if minWidthParam == minHeightParam, it can be calculated because we check when getting input.
        return 0;
    } else return CalcPossibleSectionNumForkxt(mainWidthParam, mainHeightParam, minHeightParam, minWidthParam);  // k parameter equals to minHeightParam, and t parameter equals to minWidthParam
}

/*
w = main width
h = main height
mw = minimum width
mh = minimum height
*/

/*
mw < mh    mh > w    mh <= w    mh < mw    mw > h    mw <= h    (mw < mh) ∧ (mh > w)    (mw < mh) ∧ (mh <= w)    (mh < mw) ∧ (mw > h)    (mh < mw) ∧ (mw <= h)    ((mw < mh) ∧ (mh > w)) ∨ ((mh < mw) ∧ (mw > h))
   T          T          F         F          F         T                 T                       F                        F                       F                                     T
   T          F          T         F          T         F                 F                       T                        F                       F                                     F
   F          F          T         T          T         F                 F                       F                        T                       F                                     T
   F          T          F         T          F         T                 F                       F                        F                       T                                     F
*/

/*
If the condition in the if statement of the above method is true, it will invalidate the two conditions in the if and else-if blocks inside the else block of the method below.
In this case, if the control value returned from the above method is 0, there is no need to check again, and we directly return the value of "all_possible_section_num".
If the condition in the if statement of the above method is false, 
we cannot determine whether the condition in the if block inside the else block or the condition in the else-if block inside the else block in the method below is true.
However, we can reduce these conditions. The reduction is indicated in the comments next to the if and else-if blocks.
*/

big CalcAllPossibleSectionNumber(big mainWidthParam, big mainHeightParam, big minWidthParam, big minHeightParam) {
    big all_possible_section_num = CalcPossibleSectionNumForMinWidthxMinHeight(mainWidthParam, mainHeightParam, minWidthParam, minHeightParam);  // initial
    big control_value = CalcPossibleSectionNumForMinHeightxMinWidth(mainWidthParam, mainHeightParam, minWidthParam, minHeightParam);
    if(control_value == 0) return all_possible_section_num;
    else {
        all_possible_section_num += control_value;
        if(minWidthParam < minHeightParam) {  // instead of minWidthParam < minHeightParam && minHeightParam <= mainWidthParam
            all_possible_section_num -= CalcPossibleSectionNumForkxt(mainWidthParam, mainHeightParam, minHeightParam, minHeightParam);  // k & t parameters equal to minWidthParam
        } else if (minHeightParam < minWidthParam) {  // instead of minHeightParam < minWidthParam && minWidthParam <= mainHeightParam
            all_possible_section_num -= CalcPossibleSectionNumForkxt(mainWidthParam, mainHeightParam, minWidthParam, minWidthParam);  // k & t parameters equal to minHeightParam
        }
    }
    return all_possible_section_num;
}

int main() {
    big main_width, main_height, min_width, min_height;

    Query("main width");
    GetMainPixelSize(main_width);
    Query("main height");
    PixelSizeControl(main_height);
    GetMinSectionPixelSize(main_width, min_width, "minimum width");
    GetMinSectionPixelSize(main_height, min_height, "minimum height");

    big possible_section_num_for_minwidth_x_minheight = CalcPossibleSectionNumForMinWidthxMinHeight(main_width, main_height, min_width, min_height);
    big possible_section_num_for_minheight_x_minwidth = CalcPossibleSectionNumForMinHeightxMinWidth(main_width, main_height, min_width, min_height);
    big all_possible_section_num = CalcAllPossibleSectionNumber(main_width, main_height, min_width, min_height);

    cout << "Number of possible section number for min_width x min_height: " << possible_section_num_for_minwidth_x_minheight.to_string() << endl;
    cout << "Number of possible section number for min_height x min_width: " << possible_section_num_for_minheight_x_minwidth.to_string() << endl;
    cout << "Number of all possible sections: " << all_possible_section_num.to_string() << endl;
    return 0;
}