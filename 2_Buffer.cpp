#include <iostream>
class Buffer{
    char *data_;
    size_t size_;
public:
Buffer(size_t size): data_(size>=0 ? new char[size]:nullptr), size_(size){
        std::cout<<" constructor executed \n";

}
//copy constructor
    Buffer(Buffer &other){
        //copy consturctor
        std::cout<<"copy constructor executed \n";
        if(other.size_ >0 ){
            size_ = other.size_;
            data_ = new char[size_];
            //copy 
            std::memcpy(data_,other.data_,size_);
        }
        else
        data_ = nullptr;
    }
//Move constructor
    Buffer( Buffer &&other):data_(other.data_),size_(other.size_){
        std::cout<<"move constructor executed \n";

        //move constructor
        other.data_ = nullptr;
        other.size_ = 0;
    }
//copy assignment 
//Buffer b;
// Buffer b2 = b;
    Buffer& operator=(const Buffer &other){
        if(this!= &other){
        std::cout<<"copy assignment executed \n";

            //
            char *newData = other.size_ > 0 ? new char[other.size_]:nullptr;
            if(other.size_ >0)
            std::memcpy(newData,other.data_,size_);
            
            //delte old data
            delete []data_;
            data_ = newData;
            size_ = other.size_;

        }
        return *this;
    }

    //move assignment
    Buffer& operator=(const Buffer&& other){
        //move assignment ;
        std::cout<<"move assignment constructor executed \n";

        if(this!=&other){
            //delete data first 
            delete []data_;
            //otherwise it will be dngling
            size_ = other.size_;
            data_ = other.data_;

            delete []other.data_;
            size_=0 ;
        }
        return *this;
    }
    ~Buffer(){
        delete []data_;
    }
    std::size_t size()const {
        return size_;
    }
    char* data() noexcept{
        return data_;
    }//for char* ptr = cb.data();
    const char* data() const noexcept{
        return data_;
    }//for const char *cptr = cb.data()
};

int main(int argc, char const *argv[])
{
    Buffer b(10);
    Buffer b1(b);//copy
    b1= b;//copy assignment
    // Buffer bb(std::move(b));//move constructor
    Buffer bb1= std::move(b); //move assignment


    return 0;
}
