#include "GraduatedStudent.h"

int main()
{
	unsigned grades1[] = { 3, 3, 4, 4, 5, 5 };
	GraduatedStudent gs1("Atanas", grades1, sizeof(grades1) / sizeof(unsigned), "Winning!");
	
	std::cout << "Average grade of " << gs1.name() << " is " << gs1.averageGrade() << std::endl;
	std::cout << "Average grade for all students is " << GraduatedStudent::averageGradeForAllGraduates() << std::endl << std::endl;
	
	unsigned grades2[] = { 3, 2, 2, 3 };
	GraduatedStudent gs2("Ivan Angelov", grades2, sizeof(grades2) / sizeof(unsigned), "Losing!");
	
	std::cout << "Average grade of " << gs2.name() << " is " << gs2.averageGrade() << std::endl;
	std::cout << "Average grade for all students is " << GraduatedStudent::averageGradeForAllGraduates() << std::endl << std::endl;
	
	unsigned grades3[] = { 6, 6, 6, 6, 6 };
	{
	    	GraduatedStudent gs3("Zahari", grades3, sizeof(grades3) / sizeof(unsigned), "Best of the best!");
	
	    	std::cout << "Average grade of " << gs3.name() << " is " << gs3.averageGrade() << std::endl;
	    	std::cout << "Average grade for all students is " << GraduatedStudent::averageGradeForAllGraduates() << std::endl << std::endl;
	}
	
	std::cout << "Zahari is gone....." << std::endl;
    	std::cout << "Average grade for all students is " << GraduatedStudent::averageGradeForAllGraduates() << std::endl << std::endl;
    
    	std::cout << "Changing Atanas's grades..." << std::endl;
    	gs1.setGrades(grades3, sizeof(grades3) / sizeof(unsigned));
    	std::cout << "Average grade of " << gs1.name() << " is " << gs1.averageGrade() << std::endl;
    	std::cout << "Average grade for all students is " << GraduatedStudent::averageGradeForAllGraduates() << std::endl << std::endl;
    
    	GraduatedStudent gs4(gs1);
    	std::cout << "Average grade of Atanas's copy is " << gs4.averageGrade() << std::endl;
    	std::cout << "Average grade for all students is " << GraduatedStudent::averageGradeForAllGraduates() << std::endl << std::endl;
    
    	std::cout << "All graduated students are " << GraduatedStudent::allGraduatesCount() << std::endl;
}
