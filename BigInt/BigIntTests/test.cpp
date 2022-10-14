#include "pch.h"
#include "..\BigInt\BigInt.h"

TEST(Summation, Test1) {
    BigInt a, b, c;
    a = BigInt("9999999999999999999999999999999999999999999999");
    b = BigInt(1);
    c = BigInt("10000000000000000000000000000000000000000000000");
    a += b;
    ASSERT_EQ(a, c);
}
TEST(Summation, Test2) {
    BigInt a, b, c;
    a = BigInt("986987654458873234554");
    b = BigInt("876987654323456789098723456789065432345");
    a += b;
    c = BigInt("876987654323456790085711111247938666899");
    ASSERT_EQ(c, a);
}
TEST(Summation, Test3) {
    BigInt a, b, c;
    a = BigInt("986987654458873234554");
    b = BigInt("-876987654323456789098723456789065432345");
    c = BigInt("-876987654323456788111735802330192197791");
    a += b;
    ASSERT_EQ(c, a);
}
TEST(Summation, Test4) {
    BigInt a, b, c;
    a = BigInt("380927583744750394573097935039009239053790247");
    b = BigInt("0");
    c = BigInt("380927583744750394573097935039009239053790247");
    a += b;
    ASSERT_EQ(c, a);
}
TEST(Summation, Test5) {
    BigInt a, b, c;
    a = BigInt("-986987654458873234554");
    b = BigInt("-876987654323456789098723456789065432345");
    a += b;
    c = BigInt("-876987654323456790085711111247938666899");
    ASSERT_EQ(c, a);
}
TEST(Summation, Test6) {
    BigInt a, b, c;
    a = BigInt("-986987654458873234554");
    b = BigInt("876987654323456789098723456789065432345");
    c = BigInt("876987654323456788111735802330192197791");
    a += b;
    ASSERT_EQ(c, a);
}
TEST(Summation, Test7) {
    BigInt a, b, c;
    b = BigInt("876987654323456789098723456789065432345");
    c = BigInt("876987654323456788111735802330192197791");
    a = BigInt("-986987654458873234554");
    b += a;
    ASSERT_EQ(c, b);
}
TEST(Summation, Test8) {
    BigInt a, b, c;
    a = BigInt("-986987654458873234554");
    b = BigInt("986987654458873234554");
    a += b;
    c = BigInt(0);
    ASSERT_EQ(c, a);
}
TEST(Summation, Test9) {
    BigInt a, b, c;
    a = BigInt("99999999999999999999999999999");
    b = BigInt("1111111111111111111111111111111111111111111111111");
    a += b;
    c = BigInt("1111111111111111111211111111111111111111111111110");
    ASSERT_EQ(c, a);
}
TEST(Subtraction, Test1) {
    BigInt a, b, c;
    c = BigInt("9999999999999999999999999999999999999999999999");
    b = BigInt(1);
    a = BigInt("10000000000000000000000000000000000000000000000");
    a -= b;
    ASSERT_EQ(a, c);
}
TEST(Subtraction, Test2) {
    BigInt a, b, c;
    a = BigInt("986987654458873234554");
    b = BigInt("876987654323456789098723456789065432345");
    a -= b;
    c = BigInt("-876987654323456788111735802330192197791");
    ASSERT_EQ(c, a);
}
TEST(Subtraction, Test3) {
    BigInt a, b, c;
    a = BigInt("986987654458873234554");
    b = BigInt("-876987654323456789098723456789065432345");
    a -= b;
    c = BigInt("876987654323456790085711111247938666899");
    ASSERT_EQ(c, a);
}
TEST(Subtraction, Test4) {
    BigInt a, b, c;
    c = BigInt("10000000000000000000000000000000000000000000000");
    b = BigInt(0);
    a = BigInt("10000000000000000000000000000000000000000000000");
    a -= b;
    ASSERT_EQ(a, c);
}
TEST(Subtraction, Test5) {
    BigInt a, b, c;
    a = BigInt("-986987654458873234554");
    b = BigInt("-876987654323456789098723456789065432345");
    a -= b;
    c = BigInt("876987654323456788111735802330192197791");
    ASSERT_EQ(c, a);
}
TEST(Subtraction, Test6) {
    BigInt a, b, c;
    a = BigInt("-986987654458873234554");
    b = BigInt("876987654323456789098723456789065432345");
    a -= b;
    c = BigInt("-876987654323456790085711111247938666899");
    ASSERT_EQ(c, a);
}
TEST(Dividion, Test1) {
    BigInt a, b, c;
    a = BigInt("986987654458873234554");
    b = BigInt("876987654323456789098723456789065432345");
    b /= a;
    c = BigInt("888549770973857674");
    ASSERT_EQ(c, b);
}
TEST(Dividion, Test2) {
    BigInt a, b, c;
    a = BigInt("-986987654458873234554");
    b = BigInt("876987654323456789098723456789065432345");
    b /= a;
    c = BigInt("-888549770973857674");
    ASSERT_EQ(c, b);
}
TEST(Dividion, Test3) {
    BigInt a, b, c;
    a = BigInt("-986987654458873234554");
    b = BigInt("876987654323456789098723456789065432345");
    b /= a;
    c = BigInt("-888549770973857674");
    ASSERT_EQ(c, b);
}
TEST(Dividion, Test4) {
    BigInt a, b, c;
    a = BigInt("986987654458873234554");
    b = BigInt("876987654323456789098723456789065432345");
    a /= b;
    c = BigInt("0");
    ASSERT_EQ(c, a);
}
TEST(Dividion, Test5) {
    BigInt a, b, c;
    a = BigInt("0");
    b = BigInt("876987654323456789098723456789065432345");
    a /= b;
    c = BigInt("0");
    ASSERT_EQ(c, a);
}
TEST(Division, Test6) {
    BigInt a, b;
    a = BigInt("986987654458873234554");
    b = BigInt("0");
    EXPECT_THROW(a / b, std::exception);
}
TEST(Division, Test7) {
    BigInt a, b, c;
    a = BigInt("986987654458873234554");
    b = BigInt("876987654323456789098723456789065432345");
    b %= a;
    c = BigInt("638576687345450564949");
    ASSERT_EQ(c, b);
}
TEST(Division, Test8) {
    BigInt a, b, c;
    a = BigInt("-986987654458873234554");
    b = BigInt("876987654323456789098723456789065432345");
    b %= a;
    c = BigInt("638576687345450564949");
    ASSERT_EQ(c, b);
}
TEST(Division, Test9) {
    BigInt a, b, c;
    a = BigInt("986987654458873234554");
    b = BigInt("876987654323456789098723456789065432345");
    a %= b;
    c = BigInt("986987654458873234554");
    ASSERT_EQ(c, a);
}
TEST(Multiplication, Test1) {
    BigInt a, b, c;
    a = BigInt("986987654458873234554");
    b = BigInt("876987654323456789098723456789065432345");
    b *= a;
    c = BigInt("865575987930097735046251698379192302971837774468900603249130");
    ASSERT_EQ(c, b);
}
TEST(Multiplication, Test2) {
    BigInt a, b, c;
    a = BigInt("-986987654458873234554");
    b = BigInt("876987654323456789098723456789065432345");
    b *= a;
    c = BigInt("-865575987930097735046251698379192302971837774468900603249130");
    ASSERT_EQ(c, b);
}
TEST(Multiplication, Test3) {
    BigInt a, b, c;
    a = BigInt("0");
    b = BigInt("876987654323456789098723456789065432345");
    b *= a;
    c = BigInt("0");
    ASSERT_EQ(c, b);
}
TEST(Multiplication, Test4) {
    BigInt a, b, c;
    a = BigInt("11111111111111111111");
    b = BigInt("999999999999999999999999999999");
    b *= a;
    c = BigInt("11111111111111111110999999999988888888888888888889");
    ASSERT_EQ(c, b);
}
TEST(Comparison, Test1) {
    BigInt a, b;
    a = BigInt(11111111);
    b = BigInt(11111111);
    ASSERT_EQ(true, a == b);
}
TEST(Comparison, Test2) {
    BigInt a, b;
    a = BigInt(11111111);
    b = BigInt(11111111);
    ASSERT_EQ(false, a != b);
}
TEST(Comparison, Test3) {
    BigInt a, b;
    a = BigInt(11111111);
    b = BigInt(11111111);
    ASSERT_EQ(false, a > b);
}
TEST(Comparison, Test4) {
    BigInt a, b;
    a = BigInt(11111111);
    b = BigInt(11111111);
    ASSERT_EQ(true, a <= b);
}
TEST(Comparison, Test5) {
    BigInt a, b;
    a = BigInt(11111111);
    b = BigInt(11111111);
    ASSERT_EQ(true, a >= b);
}
TEST(Comparison, Test6) {
    BigInt a, b;
    b = BigInt(11111111);
    a = BigInt("345678900987639854456789765433789987654");
    ASSERT_EQ(false, a == b);
}
TEST(Comparison, Test7) {
    BigInt a, b;
    b = BigInt(11111111);
    a = BigInt("345678900987639854456789765433789987654");
    ASSERT_EQ(true, a != b);
}
TEST(Comparison, Test8) {
    BigInt a, b;
    b = BigInt(11111111);
    a = BigInt("345678900987639854456789765433789987654");
    ASSERT_EQ(false, a < b);
}
TEST(Comparison, Test9) {
    BigInt a, b;
    b = BigInt(11111111);
    a = BigInt("345678900987639854456789765433789987654");
    ASSERT_EQ(true, a > b);
}
TEST(Comparison, Test10) {
    BigInt a, b;
    b = BigInt(11111111);
    a = BigInt("345678900987639854456789765433789987654");
    ASSERT_EQ(false, a <= b);
}
TEST(Comparison, Test11) {
    BigInt a, b;
    b = BigInt(11111111);
    a = BigInt("345678900987639854456789765433789987654");
    ASSERT_EQ(true, a >= b);
}
TEST(AndOr, Test1) {
    BigInt a, b, c;
    a = BigInt("790739073957309234923903750937537");
    b = BigInt("58380923809382094239572930523094");
    c = BigInt("58353611449718685259486839868352");
    a &= b;
    ASSERT_EQ(c, a);
}
TEST(AndOr, Test2) {
    BigInt a, b, c;
    a = BigInt("753794827409235039573709574097375475093509");
    b = BigInt("-573945739857");
    c = BigInt("753794827409235039573709574096825706676229");
    a &= b;
    ASSERT_EQ(c, a);
}
TEST(AndOr, Test3) {
    BigInt a, b, c;
    a = BigInt("-343795872347037509430957293407293407");
    b = BigInt("48734373834839490238");
    c = BigInt("48734302899015790624");
    a &= b;
    ASSERT_EQ(c, a);
}
TEST(AndOr, Test4) {
    BigInt a, b, c;
    a = BigInt("-3558273375094093457284572450724856468946586519355894");
    b = BigInt("-3587853651465983139854958164895613985465891459859159");
    c = BigInt("-3587872205719002395924094709261605521402321692443640");
    a &= b;
    ASSERT_EQ(c, a);
}
TEST(AndOr, Test5) {
    BigInt a, b, c;
    a = BigInt("0");
    b = BigInt("-3587853651465983139854958164895613985465891459859159");
    c = BigInt("0");
    a &= b;
    ASSERT_EQ(c, a);
}
TEST(AndOr, Test6) {
    BigInt a, b, c;
    a = BigInt("11111111111111111111111111111111111");
    b = BigInt("9774237472093479482390424934");
    c = BigInt("11111115927505870134702719880887783");
    a |= b;
    ASSERT_EQ(c, a);
}
TEST(AndOr, Test7) {
    BigInt a, b, c;
    a = BigInt("9583984098904393943908");
    b = BigInt("-894234937523472904390239407359730937590379305790593394948");
    c = BigInt("-894234937523472904390239407359730928135533468604925304836");
    a |= b;
    ASSERT_EQ(c, a);
}

TEST(AndOr, Test8) {
    BigInt a, b, c;
    a = BigInt("-7847987847023473730943904");
    b = BigInt("3747387394239849348293482394082309384094830948");
    c = BigInt("-2897762422409521668303516");
    a |= b;
    ASSERT_EQ(c, a);
}
TEST(AndOr, Test9) {
    BigInt a, b, c;
    a = BigInt("-4872387384740937903247947343942934890384939");
    b = BigInt("-898329482340992490489034947");
    c = BigInt("-665006756478132231898957827");
    a |= b;
    ASSERT_EQ(c, a);
}
TEST(AndOr, Test10) {
    BigInt a, b, c;
    a = BigInt("-4872387384740937903247947343942934890384939");
    b = BigInt("0");
    c = BigInt("-4872387384740937903247947343942934890384939");
    a |= b;
    ASSERT_EQ(c, a);
}
TEST(AndOr, Test11) {
    BigInt a, b, c;
    a = BigInt("-4872387384740937903247947343942934890384939");
    b = BigInt("0");
    c = BigInt("-4872387384740937903247947343942934890384939");
    a |= b;
    ASSERT_EQ(c, a);
}
TEST(XorNot, Test1) {
    BigInt a, b, c;
    a = BigInt("76543234567890482989280498409238");
    b = BigInt("38594789459835237438495638945638");
    c = BigInt("43198839165974010001589567103088");
    a ^= b;
    ASSERT_EQ(c, a);
}
TEST(XorNot, Test2) {
    BigInt a, b, c;
    a = BigInt("3558273375094093457284572450724856468946586519355894");
    b = BigInt("-3587853651465983139854958164895613985465891459859159");
    c = BigInt("-29617384877928194708658802902740588392165405672225");
    a ^= b;
    ASSERT_EQ(c, a);
}
TEST(XorNot, Test3) {
    BigInt a, b, c;
    a = BigInt("-8394950294848");
    b = BigInt("4827170129301949819483923509240924790375204128390423949429");
    c = BigInt("-4827170129301949819483923509240924790375204126884668443979");
    a ^= b;
    ASSERT_EQ(c, a);
}
TEST(XorNot, Test4) {
    BigInt a, b, c;
    a = BigInt("-7358958374284572938209908945839482394");
    b = BigInt("-49382085944943934948903458348903489034894589903343734");
    c = BigInt("49382085944943940885146976935855752169392470718805612");
    a ^= b;
    ASSERT_EQ(c, a);
}
TEST(XorNot, Test5) {
    BigInt a, b, c;
    a = BigInt("86836482623470597582748237502374892783483693642");
    b = BigInt("0");
    a ^= b;
    c = BigInt("86836482623470597582748237502374892783483693642");
    ASSERT_EQ(c, a);
}
TEST(XorNot, Test6) {
    BigInt a, b, c;
    a = BigInt("986987654458873");
    c = BigInt("-986987654458874");
    b = ~a;
    ASSERT_EQ(c, b);
}
TEST(XorNot, Test7) {
    BigInt a, b, c;
    a = BigInt(0);
    a = ~a;
    c = BigInt(-1);
    ASSERT_EQ(c, a);
}
TEST(XorNot, Test8) {
    BigInt a, b, c;
    a = BigInt("-986987654458873");
    c = BigInt("986987654458872");
    b = ~a;
    ASSERT_EQ(c, b);
}
TEST(IntString, Test1) {
    BigInt a = "23867387276293623629836834698623942386376826986389676";
    int c = 238673872;
    int b = int(a);
    ASSERT_EQ(c, b);
}
TEST(IntString, Test2) {
    BigInt a;
    int c, b;
    a = BigInt("-23867387276293623629836834698623942386376826986389676");
    c = -238673872;
    b = int(a);
    ASSERT_EQ(c, b);
}
TEST(IntString, Test3) {
    BigInt a;
    int c, b;
    a = BigInt("-214748364993623629836834698623942386376826986389676");
    c = -214748364;
    b = int(a);
    ASSERT_EQ(c, b);
}
TEST(IntString, Test4) {
    BigInt a;
    int c, b;
    a = BigInt("-214748364993623629836834698623942386376826986389676");
    c = -214748364;
    b = int(a);
    ASSERT_EQ(c, b);
}
TEST(IntString, Test5) {
    BigInt a;
    a = BigInt("214748364993623629836834698623942386376826986389676");
    std::string s = "214748364993623629836834698623942386376826986389676";
    std::string m = std::string(a);
    ASSERT_EQ(s, m);
}
TEST(IntString, Test6) {
    EXPECT_THROW(BigInt("42353524232352323*23423*4*2"), std::invalid_argument);
}