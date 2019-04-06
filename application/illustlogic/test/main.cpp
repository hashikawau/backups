
#include <iostream>
#include <vector>



int main(int argc, char* argv[])
{
    //-----------------------------------------------------
    //  problem:
    //           1
    //           1 3
    //         4 1 1 3
    //       +--------
    //      4|
    //    1 1|
    //      1|
    //    1 1|
    //      4|
    //
    //  solution: = 'B'
    //           1
    //           1 3
    //         5 1 1 3
    //       +--------
    //      3| * * *
    //    1 1| *   *
    //      4| * * * *
    //    1 1| *     *
    //      4| * * * *
    //
    //  method:
    //    process[0]
    //           1
    //           1 3
    //         5 1 1 3
    //       +--------
    //      3|   * *
    //    1 1|
    //      4| * * * *
    //    1 1| 
    //      4| * * * *
    //
    //    process[1]
    //           1
    //           1 3
    //         5 1 1 3
    //       +--------
    //      3| * * * -
    //    1 1| * - * -
    //      4| * * * *
    //    1 1| * - - *
    //      4| * * * *
    //-----------------------------------------------------
    enum BoxState: unsigned char
    {
        UNKNOWN =0,
        WHITE,
        BLACK,
        OTHERHINT,
    };
    typedef std::vector<std::vector<BoxState>> BoxStateMatrix;
    typedef std::vector<unsigned int> HintsOfLine;

    //-----------------------------------------------------
    // initialize
    //-----------------------------------------------------
    const unsigned int rows =5;
    const unsigned int cols =4;

    //
    BoxStateMatrix mat(rows);
    for(int i=0; i< rows; ++i)
    {
        mat.at(i).resize(cols);
        for(int j=0; j< cols; ++j)
        {
            mat[i][j] = BoxState::UNKNOWN;
        }
    }

    //
    const std::vector<HintsOfLine> hintsofrows = {
        HintsOfLine{   3},
        HintsOfLine{1, 1},
        HintsOfLine{   4},
        HintsOfLine{1, 1},
        HintsOfLine{   4},
    };

    //
    const std::vector<HintsOfLine> hintsofcols = {
        HintsOfLine{      5},
        HintsOfLine{1, 1, 1},
        HintsOfLine{   3, 1},
        HintsOfLine{      3},
    };

    //-----------------------------------------------------
    // solve
    //-----------------------------------------------------
    // a hint solver
    auto procahint = [](const std::vector<BoxState>& boxstates, const unsigned int ahint) -> std::vector<BoxState>{
        //-----------------------------------------------------
        //
        //-----------------------------------------------------

        std::vector<BoxState> result;
        return result;
    };

    // line hint solver
    auto procline = [](const std::vector<BoxState>& boxstates, const HintsOfLine& hintsofline) -> std::vector<BoxState>{
        //-----------------------------------------------------
        // try to find a inserting hint place
        //-----------------------------------------------------
        std::vector<std::vector<BoxState>> lineboxstateList;
        lineboxstateList.reserve(hintsofline.size());
        for(const unsigned int hint: hintsofline)
        {
            // prepare boxstates for procahint()
            //auto re = procahint();
            //lineboxstateList.push_back(re);
        }
        // merge lineboxstateList to result as a line hint solution
        std::vector<BoxState> result;

        return result;
    };

    // TODO: parallelize
    //std::vector<decltype(procline)> tasklist;
    //while(!tasklist.empty())
    //{
    //    std::vector<BoxState> result = tasklist.front()(boxstates, hintsofline);
    //}

    //-----------------------------------------------------
    // output solution
    //-----------------------------------------------------
    for(const std::vector<BoxState>& m: mat)
    {
        for(const BoxState s: m)
        {
            std::cout << (
                s == 0? '-':
                s == 1? ' ':
                '*'
            ) << "";
        }
        std::cout << std::endl;
    }

//    int numline;
//    int offset;
//    int step;
//    if(indexline < _numver){
//        numline = _numhor;
//        offset  = indexline *_numhor;
//        step    = 1;
//    }else
//    if(indexline < _numver +_numhor){
//        numline = _numver;
//        offset  = indexline -_numver;
//        step    = _numhor;
//    }else{
//        throw String("error at line ")
//            +String(indexline)
//            +String(" - initialization");
//    }

//    //==================================================================
//    bool flagblack[numline];
//    bool flagwhite[numline];
//    bool isfinished =true;
//    for(int i=0; i< numline; ++i){
//        flagblack[i] = _flagblack[offset +step *i];
//        flagwhite[i] = _flagwhite[offset +step *i];
//        isfinished &= flagblack[i] | flagwhite[i];
//    }
//    if(isfinished){
//        return true;
//    }
//    if(!_ischanged[indexline]){
//        return false;
//    }

//    //==================================================================
//    int numblack = _numblack[indexline];
//    int blacks[numblack];
//    for(int i=0; i< numblack; ++i){
//        blacks[i] = _blacks[indexline][i];
//    }

//    //==================================================================
//{//
//    /*//bool isblack =false;
//    int countblack =0;
//    int countstring =0;
//    for(int j=0; j< numline; ++j){
//        if(flagblack[j]){
//            ++countstring;
//        }else{
//            if(countstring >0){
//                if(countblack < numblack){
//                    if(countstring == blacks[countblack]){
//                        ++countblack;
//                    }else{
//                        countstring =-1;
//                        break;
//                    }
//                }else{
//                    countstring =-1;
//                    break;
//                }
//            }
//            countstring =0;
//        }
//    }
//    if(countstring >0){
//        if(countblack < numblack){
//            if(countstring == blacks[countblack]){
//                ++countblack;
//                countstring =0;
//            }else{
//                countstring =-1;
//            }
//        }else{
//            countstring =-1;
//        }
//    }
//    if(countblack == numblack && countstring ==0){
//        return true;
//    }
//    if(!_ischanged[indexline]){
//        return false;
//    }*/
//}//

//    //==================================================================
//    bool blackhead[numblack][numline];
//    for(int i=0; i< numblack; ++i){
//        bool doexist =true;
//        for(int j=0; j< numline; ++j){
//            blackhead[i][j] = true;
//            doexist &= blackhead[i][j];
//        }
//    }

//    //==================================================================
//    bool prevflagblack[numline];
//    bool prevflagwhite[numline];
//    bool prevblackhead[numblack][numline];
//    //ismuch =true;
//    for(int j=0; j< numline; ++j){
//        //ismuch &= prevflagblack[j] == flagblack[j];
//        //ismuch &= prevflagwhite[j] == flagwhite[j];
//        prevflagblack[j] = flagblack[j];
//        prevflagwhite[j] = flagwhite[j];
//        for(int i=0; i< numblack; ++i){
//            prevblackhead[i][j] = blackhead[i][j];
//        }
//    }
//    bool ismuch =false;

//    //==================================================================
//    while(!ismuch){
//        
//        //chamber
//        //==================================================================
//        int numchamber =0;
//{//numchamber
//        bool iswhite =true;
//        for(int j=0; j< numline; ++j){
//            if(flagwhite[j]){
//                iswhite =true;
//            }else{
//                if(iswhite){
//                    ++numchamber;
//                    //++countchamber;
//                    //chamberhead[countchamber] = j;
//                }
//                iswhite =false;
//                //++sizechamber[countchamber];
//            }
//        }
//}//numchamber

//        //==================================================================
//        int chamberhead[numchamber];
//        int sizechamber[numchamber];
//{//chamberhead, sizechamber
//        for(int i=0; i< numchamber; ++i){
//            sizechamber[i] =0;
//        }
//        bool iswhite =true;
//        int countchamber =-1;
//        for(int j=0; j< numline; ++j){
//            if(flagwhite[j]){
//                iswhite =true;
//            }else{
//                if(iswhite){
//                    //++numchamber;
//                    ++countchamber;
//                    chamberhead[countchamber] = j;
//                }
//                iswhite =false;
//                ++sizechamber[countchamber];
//            }
//        }
//}//chamberhead, sizechamber

//        //==================================================================
//        for(int j=0; j< numline; ++j){
//            if(flagblack[j]){
//                for(int i=0; i< numblack; ++i){
//                    if(j -blacks[i] >=0){
//                        blackhead[i][j -blacks[i]] =false;
//                    }
//                    if(j+1 < numline){
//                        blackhead[i][j+1] =false;
//                    }
//                }
//            }
//            if(flagwhite[j]){
//                for(int i=0; i< numblack; ++i){
//                    blackhead[i][j] =false;
//                }
//            }
//        }

//        //==================================================================
//        for(int k=0; k< numchamber; ++k){
//            for(int i=0; i< numblack; ++i){
//                for(int j= chamberhead[k];
//                    j< chamberhead[k] +sizechamber[k];
//                    ++j)
//                {
//                    if(sizechamber[k] < blacks[i]){
//                        blackhead[i][j] =false;
//                    }else
//                    if(blackhead[i][j]
//                        && j +blacks[i] > chamberhead[k] +sizechamber[k])
//                    {
//                        blackhead[i][j] = false;
//                    }
//                }
//            }
//        }

//        //==================================================================
//{//
//        int offsetblack =0;
//        for(int k=0; k< numchamber; ++k){
//            for(int j= chamberhead[k];
//                j< chamberhead[k] +sizechamber[k];
//                ++j)
//            {
//                if(blackhead[offsetblack][j]){
//                    int tail = j +blacks[offsetblack];
//                    if(tail <= chamberhead[k] +sizechamber[k]){
//                        ++offsetblack;
//                        if(offsetblack >= numblack){
//                            break;
//                        }
//                        for(int i= offsetblack; i< numblack; ++i){
//                            for(int j2=0;
//                                j2<= Math::min(numline -1, tail);
//                                ++j2)
//                            {
//                                blackhead[i][j2] =false;
//                            }
//                        }
//                    }else{
//                        blackhead[offsetblack][j] =false;
//                    }
//                }
//            }
//            if(offsetblack >= numblack){
//                break;
//            }
//        }
//}//
//{//
//        int offsetblack = numblack -1;
//        for(int k= numchamber -1; k>= 0; --k){
//            int indexwall = chamberhead[k] +sizechamber[k];
//            for(int j= indexwall -1;
//                j>= chamberhead[k];
//                --j)
//            {
//                if(blackhead[offsetblack][j]){
//                    int tail = j +blacks[offsetblack];
//                    if(tail <= indexwall){
//                        indexwall = j -1;
//                        --offsetblack;
//                        if(offsetblack <0){
//                            break;
//                        }
//                        for(int i= offsetblack; i>= 0; --i){
//                            for(int j2= Math::max(0, j-1);
//                                j2< numline;
//                                ++j2)
//                            {
//                                blackhead[i][j2] =false;
//                            }
//                        }
//                    }else{
//                        blackhead[offsetblack][j] =false;
//                    }
//                }
//            }
//            if(offsetblack <0){
//                break;
//            }
//        }
//}//

//        //string black
//        //==================================================================
//        int numstring =0;
//{//numstring
//        bool isblack =false;
//        for(int j=0; j< numline; ++j){
//            if(flagblack[j]){
//                if(!isblack){
//                    ++numstring;
//                    //++countstring;
//                    //stringhead[countstring] = j;
//                }
//                isblack =true;
//                //++sizestring[countstring];
//            }else{
//                isblack =false;
//            }
//        }
//}//numstring

//        //==================================================================
//        int stringhead[numstring];
//        int sizestring[numstring];
//{//stringhead, sizestring
//        for(int i=0; i< numstring; ++i){
//            sizestring[i] =0;
//        }
//        bool isblack =false;
//        int countstring =-1;
//        for(int j=0; j< numline; ++j){
//            if(flagblack[j]){
//                if(!isblack){
//                    //++numstring;
//                    ++countstring;
//                    stringhead[countstring] = j;
//                }
//                isblack =true;
//                ++sizestring[countstring];
//            }else{
//                isblack =false;
//            }
//        }
//}//stringhead, sizestring

//        //ispossible
//        //==================================================================
//        bool ispossible[numstring][numblack];
//{//ispossible
//        //==================================================================
//        bool blackoverlap[numblack][numline];
//        for(int i=0; i< numblack; ++i){
//            for(int j=0; j< numline; ++j){
//                blackoverlap[i][j] = false;
//            }
//        }
//        for(int i=0; i< numblack; ++i){
//            for(int j=0; j< numline; ++j){
//                if(blackhead[i][j]){
//                    for(int k=0; k< blacks[i]; ++k){
//                        blackoverlap[i][j +k] |= true;
//                    }
//                }
//            }
//        }

//        //==================================================================
//        for(int k=0; k< numstring; ++k){
//            for(int i=0; i< numblack; ++i){
//                ispossible[k][i] =true;
//            }
//        }
//        for(int k=0; k< numstring; ++k){
//            for(int j= stringhead[k];
//                j< stringhead[k] +sizestring[k];
//                ++j)
//            {
//                for(int i=0; i< numblack; ++i){
//                    ispossible[k][i] &= blackoverlap[i][j];
//                }
//            }
//            for(int i=0; i< numblack; ++i){
//                ispossible[k][i] &= blacks[i] >= sizestring[k];
//            }
//        }
//}//

//        //==================================================================
//        int indexchamberstring[numstring];
//        for(int k=0; k< numstring; ++k){
//            int countchamber = numchamber -1;
//            while(chamberhead[countchamber] > stringhead[k]){
//                if(--countchamber <0){
//                    throw String("error at line ")
//                        +String(indexline)
//                        +String(" - black string");
//                }
//            }
//            indexchamberstring[k] = countchamber;
//        }

//        //==================================================================
//{//
//        int indexblackdetermined[numstring];
//        for(int k=0; k< numstring; ++k){
//            indexblackdetermined[k] =-1;
//            for(int i=0; i< numblack; ++i){
//                if(ispossible[k][i]){
//                    if(indexblackdetermined[k] ==-1){
//                        indexblackdetermined[k] = i;
//                    }else{
//                        indexblackdetermined[k] =-2;
//                        break;
//                    }
//                }
//            }
//        }
//        int prevcount =0;
//        for(int k=0; k< numstring; ++k){
//            if(indexblackdetermined[k] >=0){
//                ++prevcount;
//            }
//        }

//        while(1){
//            for(int k=0; k< numstring; ++k){
//                int index = indexblackdetermined[k];
//                if(index >=0){
//                    for(int i=0; i<= index; ++i){
//                        for(int k2= k+1; k2< numstring; ++k2){
//                            if(indexchamberstring[k]
//                                != indexchamberstring[k2])
//                            {
//                                ispossible[k2][i] =false;
//                            }else{
//                                if(stringhead[k] +blacks[index]
//                                    < stringhead[k2] +sizestring[k2])
//                                {
//                                    ispossible[k2][i] =false;
//                                }
//                            }
//                        }
//                    }
//                    for(int i= index; i< numblack; ++i){
//                        for(int k2=0; k2< k; ++k2){
//                            if(indexchamberstring[k]
//                                != indexchamberstring[k2])
//                            {
//                                ispossible[k2][i] =false;
//                            }else{
//                                if(stringhead[k] +blacks[index]
//                                    < stringhead[k2] +sizestring[k2])
//                                {
//                                    ispossible[k2][i] =false;
//                                }
//                            }
//                        }
//                    }
//                }

//                indexblackdetermined[k] =-1;
//                for(int i=0; i< numblack; ++i){
//                    if(ispossible[k][i]){
//                        if(indexblackdetermined[k] ==-1){
//                            indexblackdetermined[k] = i;
//                        }else{
//                            indexblackdetermined[k] =-2;
//                            break;
//                        }
//                    }
//                }
//            }
//            int count =0;
//            for(int k=0; k< numstring; ++k){
//                if(indexblackdetermined[k] >=0){
//                    ++count;
//                }
//            }
//            if(prevcount == count){ break; }
//            prevcount = count;
//        }

//        //==================================================================
//        /*for(int k=0; k< numstring; ++k){
//            cout << indexline << ", ";
//            cout << stringhead[k] << " - ";
//            cout << sizestring[k] << ", ";
//            cout << "[ ";
//            for(int i=0; i< numblack; ++i){
//                cout << blacks[i] << " ";
//            }
//            cout << "], ";
//            cout << "chamber - " << indexchamberstring[k];
//            cout << " ==> ";
//            for(int i=0; i< numblack; ++i){
//                cout << ispossible[k][i] << " ";
//            }
//            cout << endl;
//        }*/
//        //==================================================================
//}//

//        //==================================================================
//        for(int k=0; k< numstring; ++k){
//            for(int i=0; i< numblack; ++i){
//                if(ispossible[k][i]){
//                    for(int j= stringhead[k] +1; j< numline; ++j){
//                        blackhead[i][j] =false;
//                    }
//                    break;
//                }
//            }
//        }
//        for(int k= numstring -1; k>= 0; --k){
//            for(int i= numblack -1; i>= 0; --i){
//                if(ispossible[k][i]){
//                    for(int j=0;
//                        j< stringhead[k] +sizestring[k] -blacks[i];
//                        ++j)
//                    {
//                        blackhead[i][j] =false;
//                    }
//                    break;
//                }
//            }
//        }

//        //==================================================================
//{//painting in black string
//        bool blackoverlap[numline];
//        bool whiteoverlap[numline];
//        bool blackoverlapsolo[numline];
//        bool whiteoverlapsolo[numline];
//        for(int i=0; i< numline; ++i){
//            blackoverlap[i] =false;
//            //whiteoverlap[i] =true;
//            whiteoverlap[i] =false;
//        }
//        for(int k=0; k< numstring; ++k){
//            bool blackoverlapstring[numline];
//            bool whiteoverlapstring[numline];
//            for(int j=0; j< numline; ++j){
//                blackoverlapstring[j] =true;
//                whiteoverlapstring[j] =true;
//            }
//            for(int i=0; i< numblack; ++i){
//                if(ispossible[k][i]){
//                    for(int j=0; j< numline; ++j){
//                        blackoverlapsolo[j] =true;
//                        whiteoverlapsolo[j] =true;
//                    }
//                    for(int j= Math::max(
//                            0, 
//                            stringhead[k] +sizestring[k] -blacks[i]);
//                        j<= stringhead[k];
//                        ++j)
//                    {
//                        if(blackhead[i][j]){
//                            for(int j2= 0; j2< j; ++j2){
//                                blackoverlapsolo[j2] =false;
//                            }
//                            for(int j2= j +blacks[i]; j2< numline; ++j2){
//                                blackoverlapsolo[j2] =false;
//                            }
//                            for(int j2= 0; j2< j -1; ++j2){
//                                whiteoverlapsolo[j2] =false;
//                            }
//                            for(int j2= j; j2< j +blacks[i]; ++j2){
//                                whiteoverlapsolo[j2] =false;
//                            }
//                            for(int j2= j +blacks[i] +1; j2< numline; ++j2){
//                                whiteoverlapsolo[j2] =false;
//                            }
//                        }
//                    }
//                    for(int j=0; j< numline; ++j){
//                        blackoverlapstring[j] &= blackoverlapsolo[j];
//                        whiteoverlapstring[j] &= whiteoverlapsolo[j];
//                    }
//                }else{
//
//                }
//            }

//            for(int j=0; j< numline; ++j){
//                blackoverlap[j] |= blackoverlapstring[j];
//                whiteoverlap[j] |= whiteoverlapstring[j];
//            }
//        }
//        for(int j=0; j< numline; ++j){
//            flagblack[j] |= blackoverlap[j];
//            flagwhite[j] |= whiteoverlap[j];
//        }

//        /*for(int i=0; i< numline; ++i){
//            if(flagblack[i] & flagwhite[i]){
//                throw String("error at line ")
//                    +String(indexline)
//                    +String(" - painting in black string");
//            }
//        }*/
//}//painting in black string

//    //==================================================================
//{//painting
//        bool blackoverlap[numline];
//        bool whiteoverlap[numline];
//        bool blackoverlapsolo[numline];
//        for(int i=0; i< numline; ++i){
//            blackoverlap[i] =false;
//            whiteoverlap[i] =true;
//        }
//        for(int i=0; i< numblack; ++i){
//            for(int j=0; j< numline; ++j){
//                blackoverlapsolo[j] =true;
//            }
//            for(int j=0; j< numline; ++j){
//                if(blackhead[i][j]){
//                    for(int k=0; k< j; ++k){
//                        blackoverlapsolo[k] =false;
//                    }
//                    for(int k= j; k< j +blacks[i]; ++k){
//                        whiteoverlap[k] =false;
//                    }
//                    for(int k= j +blacks[i]; k< numline; ++k){
//                        blackoverlapsolo[k] =false;
//                    }
//                }
//            }
//            for(int j=0; j< numline; ++j){
//                blackoverlap[j] |= blackoverlapsolo[j];
//            }
//        }
//        for(int j=0; j< numline; ++j){
//            flagblack[j] |= blackoverlap[j];
//            flagwhite[j] |= whiteoverlap[j];
//        }
//
//        for(int i=0; i< numline; ++i){
//            if(flagblack[i] & flagwhite[i]){
//                throw String("error at line ")
//                    +String(indexline)
//                    +String(" - painting");
//            }
//        }
//}//painting

//        //==================================================================
//        /*for(int i=0; i< numblack; ++i){
//            cout << indexline << ", " << blacks[i] << "==> ";
//            for(int j=0; j< numline; ++j){
//                cout << blackhead[i][j];
//                if(!((j+1)%5)){
//                    cout << " ";
//                }
//            }
//            cout << endl;
//        }
//        cout << endl;*/
//        //==================================================================
//
//        //==================================================================
//        ismuch =true;
//        for(int j=0; j< numline; ++j){
//            ismuch &= prevflagblack[j] == flagblack[j];
//            ismuch &= prevflagwhite[j] == flagwhite[j];
//            prevflagblack[j] = flagblack[j];
//            prevflagwhite[j] = flagwhite[j];
//
//            for(int i=0; i< numblack; ++i){
//                ismuch &= prevblackhead[i][j] == blackhead[i][j];
//                prevblackhead[i][j] = blackhead[i][j];
//            }
//        }
//    }//while

//    //==================================================================
//    int offset2 = indexline < _numver?
//        _numver:
//        0;
//    for(int j=0; j< numline; ++j){
//        /*if(!_flagblack[offset +step *j] & !_flagwhite[offset +step *j]){
//            if(flagblack[j] | flagwhite[j]){
//                _ischanged[offset2 +j] =true;
//            }
//        }*/
//        if(_flagblack[offset +step *j] != flagblack[j]
//            || _flagwhite[offset +step *j] != flagwhite[j]){
//            _ischanged[offset2 +j] =true;
//        }
//        _flagblack[offset +step *j] = flagblack[j];
//        _flagwhite[offset +step *j] = flagwhite[j];
//    }
//    _ischanged[indexline] =false;

//    //==================================================================
//    return false;

    return 0;
}



