#ifndef LIVTEST_TESTCLEARCOLOR_H
#define LIVTEST_TESTCLEARCOLOR_H
#include "Test.h"
 
namespace LivTest {

class TestClearColor :public Test {
private:
	float m_ClearColor[4];
public:
	TestClearColor();
	~TestClearColor();

	void OnRender() override;
	void OnImGuiRender() override;
};

}      // LivTest
#endif // LIVTEST_TESTCLEARCOLOR_H