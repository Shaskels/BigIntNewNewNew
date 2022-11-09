#include "pch.h"
#include "..\Prisoner'sDilemma\Modes.h"
std::vector<std::string> x = { "321", "CCD", "DCC", "DDC", "CCC" };
TEST(Strateg, AlwaysSayYes_ReturnsYes) {
	alwaysSayYesFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = (*Prisoner).makeDecision(x, 1);
	ASSERT_EQ('C', answer);
}
TEST(Strateg, AlwaysSayNo_ReturnsNo) {
	alwaysSayNoFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(x, 1);
	ASSERT_EQ('D', answer);
}
TEST(Strateg, EyeForEyeFactory_ReturnsYes) {
	eyeForEyeFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(x, 1);
	ASSERT_EQ('C', answer);
}
TEST(Strateg, EyeForEyeFactory_ReturnsNo) {
	x[4] = "DDD";
	alwaysSayYesFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(x, 1);
	ASSERT_EQ('D', answer);
}
TEST(Strateg, Statistician_ReturnsYes) {
	statisticianFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(x, 1);
	ASSERT_EQ('C', answer);
}
TEST(Strateg, Statistician_ReturnsNo) {
	x[3] = "DDD";
	statisticianFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(x, 1);
	ASSERT_EQ('C', answer);
}
TEST(Strateg, TheEqualizer_ReturnsYes) {
	statisticianFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(x, 1);
	ASSERT_EQ('C', answer);
}
TEST(Strateg, TheEqualizer_ReturnsNo) {
	x[2] = "CDC";
	x[3] = "CDD";
	statisticianFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(x, 1);
	ASSERT_EQ('D', answer);
}
TEST(Strateg, ThePredictor_ReturnsNo) {
	statisticianFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(x, 1);
	ASSERT_EQ('D', answer);
}
TEST(Strateg, ThePredictor_ReturnsYes) {
	x[0] = "311";
	statisticianFactory factory;
	Strategies* Prisoner = factory.makeStrategies();
	char answer = Prisoner->makeDecision(x, 1);
	ASSERT_EQ('C', answer);
}