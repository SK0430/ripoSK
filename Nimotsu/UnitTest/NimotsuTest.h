#pragma once
#include <cppunit/extensions/HelperMacros.h>
#include "Nimotsu.h"


class NimotsuTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( NimotsuTest );
	CPPUNIT_TEST( test_init );
	CPPUNIT_TEST( createMapTest );
	CPPUNIT_TEST( loadMapTest );
	CPPUNIT_TEST( stateTest );
	CPPUNIT_TEST( moveTest01 );
	CPPUNIT_TEST( moveTest02 );
	CPPUNIT_TEST( moveTest03 );
	CPPUNIT_TEST( moveTest04 );
	CPPUNIT_TEST( moveTest05 );
	CPPUNIT_TEST( goalTest );
	CPPUNIT_TEST( test_clear );
	CPPUNIT_TEST_SUITE_END();

protected:
	Nimotsu* m_ni;

public:
	void setUp();
	void tearDown();

protected:
	void test_init();
	void createMapTest();
	void loadMapTest();
	void stateTest();
	void moveTest01();
	void moveTest02();
	void moveTest03();
	void moveTest04();
	void moveTest05();
	void goalTest();
	void test_clear();

};