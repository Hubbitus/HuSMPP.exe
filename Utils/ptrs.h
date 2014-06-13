/////////////////////////////////////////////////////////////
// Project : SMPPRouter
// Module  : ptrs.h

#ifndef __PTRS_H__
#define __PTRS_H__

/////////////////////////////////////////////
// class to implement reference counting
// it used by CH<Type> class to automate
// Grab(), Release() methods call
// class Type must has make and destroy 
// class functions
/////////////////////////////////////////////
template <class Type>
class CMP
{
public:
  CMP() : m_Pointee( Type::Make() ), m_Count( 0 ) {}
  CMP( const CMP<Type>& cmp ) : m_Pointee( cmp.m_Pointee->Clone() ), m_Count( 0 ) { }
  ~CMP() { Type::Destroy( m_Pointee ); }

  CMP<Type>& operator = ( const CMP<Type>& cmp )
  {
    if ( this == &cmp )
      return *this;
    delete m_Pointee;
    m_Pointee = cmp.m_Pointee->Clone();
    return *this;
  }

  Type* operator -> () const { return m_Pointee; }
  operator Type* () const { return m_Pointee; }

  void Grab() { m_Count++; }
  void Release() 
  {
    if ( m_Count > 0 )
      m_Count--;
    if ( m_Count <= 0 )
      delete this;
  }

private:
  Type* m_Pointee;
  unsigned long m_Count;
};

/////////////////////////////////////////////
// class to implement reference counting
/*
// ****************************************
// everywhere use 
// CH<Type> a;
// instead
// Type* a = new Type();
// ****************************************
// Below the sample how to use it.
// ****************************************
// class A
// {
// friend class CMP<A>;
// public:
//   void Initialize() {}
//   int a;
// protected:
//   A() : a(0) {};
//   virtual ~A(){}
// private:
//   A( const A& );
//   A& operator = ( const A& );
// };
//
// void fn1()
// {
// ...
//   CH<A> a;
//   a->Initialize();
//   a->a = 5;
// ...
// }
// ****************************************
*/
/////////////////////////////////////////////
template <class Type>
class CH
{
public:
  //
  CH() : m_Pointee( new CMP<Type> ) { m_Pointee->Grab(); }
  CH( CMP<Type>* p ) : m_Pointee( p ) { m_Pointee->Grab(); }
  CH( const CH<Type>& ch ) : m_Pointee( ch.m_Pointee ) { m_Pointee->Grab(); }
  ~CH() { m_Pointee->Release(); }

  CH<Type>& operator = ( const CH<Type>& ch )
  {
    if ( this == &ch ) return *this;
    if ( m_Pointee == ch.m_Pointee ) return *this;

    m_Pointee->Release();
    m_Pointee = ch.m_Pointee;
    m_Pointee->Grab();
    return *this;
  }

  CMP<Type>& operator -> () const { return *m_Pointee; }
  operator CMP<Type>& () const { return *m_Pointee; }
  operator Type* () const { return *m_Pointee; }
private:
  CMP<Type>* m_Pointee;
};

/////////////////////////////////////////////
// class to replace simple pointers
/*
// ****************************************
// everywhere use 
// SP<Type> a;
// instead
// Type* a;
// ****************************************
*/
/////////////////////////////////////////////
template <class Type>
class SP
{
public:
  SP() : m_Pointee( NULL ) {}
  SP( Type* t ) : m_Pointee( t ) {}

  operator Type*() { return m_Pointee; }
  Type* operator -> () { return m_Pointee; }

private:
  Type* m_Pointee;
};


#pragma warning( push )
#pragma warning(disable:4189)
/////////////////////////////////////////////
template <class Base, class Derived>
inline CMP<Base>& SafeCastCMP( CMP<Derived>& objInstance )
{
  Derived* drv = objInstance;
  Base* base = drv;
  
  return ( CMP<Base>& ) objInstance;
}
#pragma warning( pop )

/////////////////////////////////////////////
template <class Base, class Derived>
inline CH<Base> SafeCastCH( CH<Derived> objInstance ){
  CH<Base> retVal( &( SafeCastCMP<Base, Derived>( objInstance ) ) );
  return retVal;
}

/////////////////////////////////////////////////////
//+78 MY
/////////////////////////////////////////////////////
#pragma warning( push )
#pragma warning(disable:4189)
template <class Derived, class Base>
inline CMP<Derived>& SafeDynamicCastCMP( CMP<Base>& objInstance ){

Base* base = objInstance;
Derived* derived = dynamic_cast<Derived*>(base);
//#pragma chMSG("ВОЗМОЖНО надо еще проверить приведение, и как-то отхандлить неудачу!??!!")
//chASSERT(derived);
#pragma chMSG("В месте вызова НЕОБХОДИМО проверить на 0 и обработать ошибку приведения, если такая была!!!")

return ( CMP<Derived>& ) objInstance;
}
#pragma warning( pop )

/////////////////////////////////////////////
template <class Derived, class Base>
inline CH<Derived> SafeDynamicCastCH( CH<Base> objInstance ){
CH<Derived> retVal( &( SafeDynamicCastCMP<Derived, Base>( objInstance ) ) );
return retVal;
}
//+78 \\\\\MY
/////////////////////////////////////////////////////

/////////////////////////////////////////////////////
#define DECLARE_CH_REFCOUNTING( Type ) \
protected: \
  Type() {} \
  virtual ~Type() {} \
private: \
  static Type* Make(); \
  static void Destroy( Type* ); \
friend class CMP<Type>;


/////////////////////////////////////////////////////
#define IMPLEMENT_CH_REFCOUNTING( IType, TypeImpl ) \
IType* \
IType::Make() \
{ \
  TypeImpl* retVal = new TypeImpl(); \
  return retVal; \
} \
void \
IType::Destroy( IType* objInstance ) \
{ \
  delete objInstance; \
}

#endif

// =================== END OF FILE =====================
////////////////////////////////////////////////////////