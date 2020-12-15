#include "hello-xmega-lib.hpp"

using namespace std;

int _nTtyAcmConnection = 0;

bool InitXmegaSerial(char* pTtyAcm, int nBaudrate, int nParity) {

  struct termios oTty;

  // A possible string?
  if (pTtyAcm == NULL) {
		//printf("No valid device name!\n");
		return false; 
  }

  // Try to open the serial connection
  //printf("[%s] ", pTtyAcm);
  _nTtyAcmConnection = open(pTtyAcm, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (_nTtyAcmConnection == 0)
	{
		perror(pTtyAcm);
	//	printf("Failed to open device: %s\n", pTtyAcm);
		return false; 
	}

  // Clear struct to start with new settings
  memset(&oTty, 0, sizeof(oTty));
  if (tcgetattr(_nTtyAcmConnection, &oTty) != 0) {
    //printf("Error %i getting settings: %s\n", errno, strerror(errno));
  };

  oTty.c_cflag |= CREAD | CS8; // Enable read, 8 bits per byte
  oTty.c_cflag &= ~(CLOCAL|CSTOPB|HUPCL|PARENB|PARODD);

  oTty.c_lflag &= ~(ECHO|ECHOE|ECHOK|ECHONL|ICANON|IEXTEN|ISIG|NOFLSH|TOSTOP); // Disable special local modes

  oTty.c_iflag &= ~(BRKINT|ICRNL|IGNBRK|IGNCR|IGNPAR|INLCR|INPCK|ISTRIP|IXOFF|IXON|PARMRK); // Disable any special handling of received bytes
	
  oTty.c_oflag &= ~(OPOST|OLCUC|ONLCR|OCRNL|ONOCR|ONLRET|OFILL|OFDEL|NLDLY|CRDLY|TABDLY|XTABS|BSDLY|VTDLY|FFDLY);  // Disable any special handling of send bytes

  oTty.c_cc[VTIME] = 1;           // Wait for up to 1s (1 deciseconds), returning as soon as any data is received.
  oTty.c_cc[VMIN] = 0;            // Minimal 0 chars read

  cfsetispeed(&oTty, nBaudrate);
  cfsetospeed(&oTty, nBaudrate);

  // Clear buffer and set new settings
  tcflush(_nTtyAcmConnection, TCIFLUSH);
  if (tcsetattr(_nTtyAcmConnection, TCSANOW, &oTty) != 0) {
    //printf("Error %i setting settings: %s\n", errno, strerror(errno));
  };

  return true;
};

bool XmegaReadByte(uint8_t* nByte) {

  ssize_t nSize;

  // Check for valid open connection
  if (_nTtyAcmConnection == 0) {
    return false;
  }

  // Read one byte only
  nSize = read(_nTtyAcmConnection, nByte, 1);
  if (nSize == -1 && errno == 11) {
    return false;
  }
  if (nSize == 0) {
    return false;
  }

  if (nSize == -1) {
    //printf("Error reading: %s", strerror(errno));
    return false;
  }

  return true;
};

bool XmegaWriteByte(uint8_t* nByte) {

  ssize_t nSize;

  // Check for valid open connection
  if (_nTtyAcmConnection == 0) {
    return false;
  }
  // Read one byte only
  nSize = write(_nTtyAcmConnection, nByte, 1);
  if (nSize != 1) {
    return false;
  };

  return true;
};

bool CloseXmegaSerial() {

  if (_nTtyAcmConnection != 0) {
    close(_nTtyAcmConnection);
  }

  return true;
};