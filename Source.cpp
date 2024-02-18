#include <iostream>


template <typename T>
class DinamicArr {
public:
	DinamicArr() : data_(nullptr), size_(0), capasity_(0) {} ///  Конструктор по умолчанию. Заполняет все поля нулями, указатель массива (data_) в позиции nullptr.
		
	DinamicArr(const DinamicArr<T>& other)  /// Конструктор копирования
	{
		size_ = other.size_;                /// Присваиваем текущему объекту размер переданного объекта 
		capasity_ = other.capasity_;        /// Ёмкость объекта становится равной размеру объекта
		data_ = other.data_;                /// Инициализация указателя на массив значением 'nullptr'
		if (size_ != 0)                     /// Если размер не равен 0, то выделяем новую память для массива размером 'size_'
		{
			data_ = new T[size_];      
		}
		else                                /// Иначе, устанавливаем указатель на массив = '0'
			data_ = 0;
		for (size_t i = 0; i < size_; i++)  /// Копируем элементы переданного массива в имеющийся
		{
			data_[i] = other.data_[i];
		}
	}

	DinamicArr(size_t size)                 /// Создание массива с переданным размером
	{
		size_ = size;
		capasity_ = size;
		if (size != 0)
		{
			data_ = new T[size];
		}
		else
			data_ = 0;
	}

	T* begin()                              
	{
		return data_;
	}
	/*! Для использования цикла range for используем указатели на начало
	и конец массива  */
	T* end()
	{
	return (size_ + data_);                  
	}
	
	/*! \brief
	Метод добавления элемента в конец массива.
	При добавление элементов в массив, если его вместимость достигла текущего максимума (capacity_),
	увеличиваем размер и максимум вместительности
	*/

	void Push_back(T unit)
	{
		if (size_ == capasity_)
		{
			capasity_ = (capasity_ == 0) ? 1 : capasity_ * 2;
			T* new_data = new T[capasity_];
			for (size_t i = 0; i < size_; i++) 
			{
				new_data[i] = data_[i];
			}
			delete[] data_;
			data_ = new_data;
		}
		data_[size_++] = unit;
	}

	/*! \brief
	Метод удаления последнего элемента с уменьшением размера массива 
	*/

	void Pop_back()
	{
		if (size_ > 0) { size_--; }
	}

	/*! \brief
	Метод добавления элемента в указанную позицию массива
	и проверкой на наличие места с добавлением при необходимости
	*/

	void Add_specified_position(size_t position, const T& obj)
	{
		if (position > size_) { throw - 1; }             /// Возвращаем исключение если переданная позиция больше размера массива

		if (size_ == capasity_)                          /// Увеличиваем вместимость и размер при достижение максимума
		{
			capasity_ = (capasity_ == 0) ? 1 : capasity_ * 2;
			T* new_data = new T[capasity_];
			for (size_t i = 0; i < size_; i++)
			{
				new_data[i] = data_[i];
			}
			new_data[position] = obj;
			for (size_t i = position; i < size_; i++)
			{
				new_data[i] = data_[i];
			}
			delete[]data_;
			data_ = new_data;
		}
		else
		{
			for (size_t i = size_; i > position; i--)
			{
				data_[i] = data_[i - 1];
			}
			data_[position] = obj;
		}
		size_++;
	}

	size_t size()const { return size_; }                   ///  Возвращает размер массива

	/*!\brief 
	Перегруженный оператор для доступа к элементам массива
	\return Ссылку на элемент массива с переданным индексом
	*/

	T& operator[] (size_t index) { return data_[index]; }

	const T& operator[] (size_t index) const { return data_[index]; }	

	~DinamicArr()                                       /// Деструктор класса для освобождения памяти
	{
		if (data_) { delete[] data_; }
	}

private:
	T* data_;         /// указатель на массив
	size_t capasity_; /// вместимость массива
	size_t size_;     /// размер массива 
};

int main() {
	setlocale(LC_ALL, "ru");

	std::cout << "Создаем массив и добавляем 1 элемент.\n";

	DinamicArr<int> arr1;
	arr1.Push_back(1);
	std::cout << "Размер массива-> " << std::size(arr1) << '\n';
	std::cout << "\n\n";
	std::cout << "Добавляем еще несколько элементов.\n";
	arr1.Push_back(2);
	arr1.Push_back(3);
	arr1.Push_back(4);
	arr1.Push_back(5);
	std::cout << "Размер массива-> " << std::size(arr1) << '\n';
	std::cout << "Состав массива: ";
	for (const auto& i : arr1) {
		std::cout << i << ", ";
	}
	std::cout << "\n\n";
	std::cout << "Дбавляем еще элемент \'50\' на 3 позицию в массиве\n";
	arr1.Add_specified_position(3, 50);
	std::cout << "и удаляем последний элемент массива.\n";
	arr1.Pop_back();

	std::cout << "Размер массива-> " << std::size(arr1) << '\n';

	for (const auto& i : arr1) {
		std::cout << i << ", ";
	}

	return 0;

}