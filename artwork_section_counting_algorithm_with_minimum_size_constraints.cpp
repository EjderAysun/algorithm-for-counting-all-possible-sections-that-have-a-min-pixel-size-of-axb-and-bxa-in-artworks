#include <iostream>
#include <limits>
#include "BigInt/include/operators/arithmetic_assignment.hpp"
#include "BigInt/include/operators/io_stream.hpp"

using namespace std;
typedef BigInt big;
typedef string str;

const int LOWER_LIMIT_OF_MIN_SECTION_SIZE = 0;

/*
w = main width
h = main height
mW or m_w = minimum width
mH or m_h = minimum height
*/

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

big CalcPossibleSectionNumForkxt(big a, big b, big k, big t) {  // a and b are main values, and k and t are minimum values

    big aCons = a - k;
    big bCons = b - t;

    return (aCons + 1) * (aCons + 2) * (bCons + 1) * (bCons + 2) / 4;

    /*
    formula: (width - minWidth + 1) * (width - minWidth + 2) * (height - minHeight + 1) * (height - minHeight + 1) / 4
    */
}

// Parameter order for the following 3 methods: main width, main height, min width, min height
// Please use this order for correct result.
// The values for main width / minimum width and main height / minimum height are in the order you wrote while getting input, using the classic size order (width x height).

big CalcPossibleSectionNumForMWxMH(big w, big h, big mW, big mH) {  // These values order are checked while getting the input, so there is no need for an additional control system.
    return CalcPossibleSectionNumForkxt(w, h, mW, mH);  // k parameter equals to min width value, and t parameter equals to min height value
}

big CalcPossibleSectionNumForMHxMW(big w, big h, big mW, big mH) {  // After the values are swapped, an additional control system is needed.
    if((mW < mH && mH > w) || (mH < mW && mW > h)) {  // if mW == mH, it can be calculated because we check when getting input.
        return 0;
    } else return CalcPossibleSectionNumForkxt(w, h, mH, mW);  // k parameter equals to min height value, and t parameter equals to min width value
}

/*
mW < mH    mH > w    mH <= w    mH < mW    mW > h    mW <= h    (mW < mH) ∧ (mH > w)    (mW < mH) ∧ (mH <= w)    (mH < mW) ∧ (mW > h)    (mH < mW) ∧ (mW <= h)    ((mW < mH) ∧ (mH > w)) ∨ ((mH < mW) ∧ (mW > h))
   T          T          F          F          F        T                 T                       F                        F                       F                                     T
   T          F          T          F          T        F                 F                       T                        F                       F                                     F
   F          F          T          T          T        F                 F                       F                        T                       F                                     T
   F          T          F          T          F        T                 F                       F                        F                       T                                     F
*/

/*
If the condition in the if statement of the above method is true, it will invalidate the two conditions in the if and else-if blocks inside the else block of the method below.
In this case, if the control value returned from the above method is 0, there is no need to check again, and we directly return the value of "all_possible_section_num".
If the condition in the if statement of the above method is false, 
we cannot determine whether the condition in the if block inside the else block or the condition in the else-if block inside the else block in the method below is true.
However, we can reduce these conditions. The reduction is indicated in the comments next to the if and else-if blocks.
*/

big CalcAllPossibleSectionNumber(big w, big h, big mW, big mH) {
    big all_possible_section_num = CalcPossibleSectionNumForMWxMH(w, h, mW, mH);  // initial
    big control_value = CalcPossibleSectionNumForMHxMW(w, h, mW, mH);
    if(control_value == 0) return all_possible_section_num;
    else {
        all_possible_section_num += control_value;
        if(mW < mH) {  // instead of mW < mH && mH <= w
            all_possible_section_num -= CalcPossibleSectionNumForkxt(w, h, mH, mH);  // min1 & min2 parameters equal to min width value
        } else if (mH < mW) {  // instead of mH < mW && mW <= h
            all_possible_section_num -= CalcPossibleSectionNumForkxt(w, h, mW, mW);  // min1 & min2 parameters equal to min height value
        }
    }
    return all_possible_section_num;
}

int main() {
    big w, h, m_w, m_h;

    Query("width");
    GetMainPixelSize(w);
    Query("height");
    PixelSizeControl(h);
    GetMinSectionPixelSize(w, m_w, "minimum width");
    GetMinSectionPixelSize(h, m_h, "minimum height");

    big possible_section_num_for_mwxmh = CalcPossibleSectionNumForMWxMH(w, h, m_w, m_h);
    big possible_section_num_for_mhxmw = CalcPossibleSectionNumForMHxMW(w, h, m_w, m_h);
    big all_possible_section_num = CalcAllPossibleSectionNumber(w, h, m_w, m_h);

    cout << "Number of possible section number for minWidthxminHeight: " << possible_section_num_for_mwxmh.to_string() << endl;
    cout << "Number of possible section number for minHeightxminWidth: " << possible_section_num_for_mhxmw.to_string() << endl;
    cout << "Number of all possible sections: " << all_possible_section_num.to_string() << endl;
    return 0;
}