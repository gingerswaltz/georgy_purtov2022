using BankDeposit;
using System;
namespace BankDeposTests
{
    [TestClass]
    public class BankDeposTests
    {
        [TestMethod]
        public void testSetProc()
        {
        BankDepos bankDepos_test = new BankDepos();
            Assert.ThrowsException<ArgumentException>(() => bankDepos_test.setProc(15));
        }
        
        [TestMethod]
        public void testSetMoney()
        {
            BankDepos bankDepos_test = new BankDepos();
            Assert.ThrowsException<ArgumentException>(() => bankDepos_test.setMoney(-1));
        }



        [TestMethod]
        public void testSetCodeNum()
        {
            BankDepos bankDepos_test = new BankDepos();
            Assert.ThrowsException<ArgumentException>(() => bankDepos_test.setcodeNum(99999));
        }
        
        [TestMethod]
        public void testSetLicNum()
        {
            BankDepos bankDepos_test = new BankDepos();
            Assert.ThrowsException<ArgumentException>(() => bankDepos_test.setlicNum(99999));
        }

        [TestMethod]

        public void testCreateObject()
        {
            BankDepos bankDepos = new BankDepos(1,1,1111,2222);
            Assert.IsNotNull(bankDepos);
        }
        
        [TestMethod]
        public void testChangeMoney()
        {
            BankDepos bankDepos = new BankDepos();
            bankDepos.MoneyChange(-1);
            Assert.IsTrue(bankDepos.getMoney() == 0);
        }

    }


}