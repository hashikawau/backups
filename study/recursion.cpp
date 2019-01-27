
template<typename T>
struct init {
    static void execute(T* array, T _InitialValue, int _Index) {
        array[_Index] = _InitialValue;
        if(_Index > 0)
            init<T>::execute(array, _InitialValue, _Index -1);
    }
};

int main(int argc, char* argv[]){
    constexpr int num = 5;
    int array[num];
    init<int>::execute(array, 3, num);
}

