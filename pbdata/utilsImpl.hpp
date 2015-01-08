#ifndef _BLASR_UTIL_IMPL_HPP_
#define _BLASR_UTIL_IMPL_HPP_

template<typename t_file>
void CrucialOpen(std::string &fileName, t_file &file, std::ios_base::openmode mode) {
	if (mode==0)
		file.open(fileName.c_str());
	else
		file.open(fileName.c_str(), mode);

	if (!file.good()) {
		std::cout << "Could not open " << fileName << std::endl;
		exit(1);
	}
}
template<typename T_Int>
T_Int CeilOfFraction(T_Int num, T_Int denom) {
	return num / denom + ((num % denom) && 1);
}

template<typename T>
T* ProtectedNew(unsigned long size) {
    T* ptr;
    ptr = new T[size];
    if (ptr == NULL) {
        std::cout << "ERROR, allocating " << size * sizeof(T) << " bytes.";
        exit(1);
    }
    return ptr;
}

#endif
