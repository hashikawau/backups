
template<class T, T _InitialValue, int _Index>
struct init {
    inline static void execute(T* array) {
        array[_Index] = _InitialValue;
        init<T, _InitialValue, _Index -1>::execute(array);
    }
};
template<class T, T _InitialValue>
struct init<T, _InitialValue, 0> {
    inline static void execute(T* array) {
        array[0] = _InitialValue;
    }
};

int main(int argc, char* argv[]){
    constexpr int num = 5;
    int array[num];
    init<int, 3, num>::execute(array);
}

