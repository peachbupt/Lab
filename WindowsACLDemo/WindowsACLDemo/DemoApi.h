#ifndef DEMO_API_H
#define DEMO_API_H

BOOL GetAndPrintToken();
BOOL GetAndPrintSecurityDescs(const std::basic_string<TCHAR> &FNameStr);
BOOL ImpersonationTest();
void ReadProcessMIC();
BOOL CreateLowProcess();
#endif //DEMO_API_H