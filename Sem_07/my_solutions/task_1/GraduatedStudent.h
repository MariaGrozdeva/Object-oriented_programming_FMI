#pragma once
#include <cstddef>

class GraduatedStudent
{
public:
    GraduatedStudent(
        const char *name,
        const unsigned *grades,
        const std::size_t gradesCount,
        const char *quote
    );

    GraduatedStudent(const GraduatedStudent &other);

    GraduatedStudent &operator=(const GraduatedStudent &other);

    ~GraduatedStudent();

    const char *getName() const;

    const unsigned *getGrades() const;

    std::size_t getGradesCount() const;

    double getAverageGrade() const;

    const char *getQuote() const;

    void setName(const char *newName);

    void setGrades(const unsigned *newGrades, std::size_t newGradesCount);

    void setQuote(const char *newQuote);

    static double getAverageGradeForAllGraduates();

    static std::size_t getGraduatedStudentsCount();

private:
    static constexpr std::size_t MAX_QUOTE_LEN = 32;
    static unsigned graduatedStudentsCount;
    static double averageGradeSumAllGraduates;

    char *name = nullptr;
    unsigned *grades = nullptr;
    std::size_t gradesCount = 0;
    char quote[MAX_QUOTE_LEN + 1] = "";
    double averageGrade = 0;

    void updateAverageGrade();

    void addToClassData() const;

    void removeFromClassData() const;

    void updateToClassData(double oldAverageGrade) const;
};
