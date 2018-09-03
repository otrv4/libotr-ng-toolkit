#include <libotr-ng/otrng.h>

#include "../parse.h"
#include "test_helpers.h"

void otrng_toolkit_test_parse_data_message() {
  const char *data_msg =
      "?OTR:AAQDHKKD8mktib4AAAAAAQAAAAQAAAAA3tx0zejuaJ/"
      "lluHxdK+xETw2t9nxWJgjbZWjiDHD6ibwJdyURAJenucUz9pHMkrwxfEpldE+"
      "sr2AAAABgINwoW3ufscly5eMIqj+"
      "HxuayAKNFr0woDbJX203VcHqmI29zC6GbVMwXS4HV8jMxtIulwpX1V/"
      "biQa0mQRqfdRLCnKHtrkhPly212rZzajHUF34TGaznfW/rB68+VELAYy9P9gEg/"
      "Vjup7qDBd7JWlIXYbrKt5vqfXlgyKWNlLUQrRc8ppwzrP5jnPh+"
      "dB5tcEXvx7nISAC3Hjlt83JmEGIDuSqzi4K4WdeNwB9wfU90ITaEdt+"
      "1lqeYcd9XBfLIxQhJFyqFrYURt/1dC0DyhIGHCi95GTtnOp8qTlzp69/egWDYg/"
      "SCLDKMiAA3RSliUMlEsXQZNNOTvY5oVsZir4P4ur5bo+mACgLkS+"
      "zt78p6saLIEYDRwIgnKJ2GSN3Tqkij4Xz4O297Ug3YzUn/mg9pFmAXkPbJwFH/"
      "929cz88HznqENfPIcVbFyJfGsFmXIJc2wWROLhLCtgy4F20ShwH4aWwdEA/"
      "vqi9E2dxsL2XSGbG60zNTEVb+"
      "Q9BQMawm6pWppRz2kQ9Tpr80Km9sTO8zonbZwLtwwAAAP8hxmJj8/"
      "HHIm1KPYKa3SFHEeJFwbgvHOqFTNNeEdmwhw/"
      "nF1JBFfqZh7R2sjFYfYoxa28Njs4osVm4UsrPPbFhZQzkifL/gIL+M8yZTLgLdd/3w/"
      "tlNj2+RLjYiwk6aQ1PFGYj/"
      "iIKbYRwtKtLwm2o2ruKCsj8G0D9G3HumiW7SPNEjuzav7KUFOigY80dd/"
      "2Gp2aq8Jd1oTrxICDJFlStKgWGki+M8gZeYUngVoBJNv+ZSzr64iT3mEwVXbPT+"
      "12TYeJNJHLWbZ6fOt6lNlT37ZFYURzgD3XEdd884aZeUQlkdFln+XA4Cut4/"
      "DM1XiWMlKBQpecVOtHwShQ2MtKopKH/bDcpMNLoC3tF0EkF4SLYPLxt/TZU/"
      "iDljTf3Lnv7NTUCte43qBl8Q4BOOVjfAzJRDQUiPECRESpbRcysg20XklPJJAyXfhvQByjW6"
      "6Df3JUQU7wEvvG2BEqSuMGq1XLNS9xAhW9NUNBizwg/"
      "dMplb6j3hqVIwMUshgO7RooM6RtxYHS6+BnEVolr5ksd2EIHgxrxH2ER+X9EKZkFM/"
      "BmpHqcB4VvSUUNquzo3N2uhxl1P6Qo14kY9fh3Uac=.";

  otrng_toolkit_assert(otrng_toolkit_parse_encoded_message(data_msg));
}

void otrng_toolkit_test_parse_identity_message() {
  const char *identity_msg =
      "?OTR:AAQ16j7KWgAAAAAAAAAEAAHqPspaAAIAEOQKxW36YA3xat70+FogpP+"
      "58B0x9sEFeMpsEFeM35Vq01InkAmEHE4HLUWRgymjS7aOX0G6aoz4gAAEAAAAAzM0AAAFAAA"
      "AAFtx1G30j7wBCbrDMb8gTNFDkNiqqbUV6fLCjErpQ9CjpYEZybd8jAl2go2i5pjhZ+"
      "eVO2kIxyF567MCV4BU/Z5utiN5lT9JDWXkpZgTQpas/IKYrSAJAe0awXskxQoKrAA/"
      "pbTasCXLLDWSyqYQXgqo1gIQNgByMJLIwvH7daO8WcznLC2OAKvizY2MN2nWGn8ZNr2L7ZX+"
      "m+BlLFvC19DwVuqP7K5a2PP/"
      "NhBdcgAAAAGAjGBp2urSLgeuyMxWBDyrLdDijIph5cocjsEBT9I2Xk4tmbz9zNDxk9a/"
      "G5tlti/Qmn5ApkMVO7Zw1l7/eoHkD3w/nkYHo7oXrwLcAI7pzgaPY7Yln+HgD1jA/"
      "4TdA5GQpAFvlNcz+wKM69c2PCAuPxgwuYBIEhXeRlolZ4A3Ekz6Um7TsPEDhlTeG/"
      "rjj8fbc+Ezmbe0filEfchYh7Y150N0ufwtA0HD2eAfp9L1CYAO/"
      "1Iwgri9v7togUltozUI+h9xyED/"
      "Pya3up6LYeNO1G9BsIZHdep9hB4RATOo1VQ3kGW3wAtqH4gKQ/"
      "1L94IpD5WKKIZFuQpDVurB1tjr3DB9LtJbrq6ePnA/"
      "xroDB07uLzwYoYpOx1ydAz9m1iweqIMvfAaGfiii+yWx2olo/"
      "KzoqcysEEZwRCKBGjostHgXGJ0OrWWsvB/lFOD/V4go4wihzkzc6vCoG51xYIYxK1OkOC/"
      "MtWZa3c6KArc3tUUcp1Orbs7sYvpNZWBHm1rt.";

  otrng_toolkit_assert(otrng_toolkit_parse_encoded_message(identity_msg));
}

void otrng_toolkit_test_parse_auth_r_message() {
  const char *auth_r_msg =
      "?OTR:AAQ2HKKD8mktib4AAAAEAAEcooPyAAIAEJ7HWugLaW5KhW5M2X8Wsa18P2RdU+"
      "hCC0X/uPtF1LbNMVPVQ2mq/q1SHPOC7La+DE65cRQ5/"
      "8JhAAAEAAAAAzM0AAAFAAAAAFtrcKUAgkfG3DHjFWUK8hk1Jf9wdOQ03xI10ZXiZzj21k6Wq"
      "0UAtbNrvMavetxfuEhrVGgu8ird+KF2X4ATcrtXttxBl8uol3S7gKP1J12GWRnpl3b7lL+"
      "rVcKt2q3Cxk5k6w9D+4btmjSpTCQxukxOmYORGAAWFCGKSTvKd1NXIxTSK+/"
      "SRaoJ606mW2TR6tlWjNZ8yGMaEQVZDTx2J0MH1Ju8wfUk8v+"
      "0lbR7awAAAAGAMvUK5YC3mzepve3LgFzcQ0w4m2BxBy/"
      "Z0LF8m8jkLMMwiklwVzcktpxD2NK7gltZCPCZP4D11IrjGuEeXip9h7168zXVixTSwmFgCev"
      "IA/fi2nlrsKkl/pGXnDTNiYejcH65PeXi/"
      "PgdxWCWMbQD1Bc1ZWn7HcfSPhDELRWq6tElCyE7cJ2pWde4drSGGF61OOmQGgT2cThBy6lju"
      "2V1NaoTv6LBO1ki+444/0jT09GUhfSoxAPTtYBjNyr54V5JpCW0N1uBwwuB0MMzfSO7V/"
      "XiwdorIREMmj2Xf/"
      "7N1r1zhLxxG6JZ4WwhahSbuArOVVwrKCvx4rI0XNvHS79MD53456gUtKan0NrDD/"
      "2Af2DVZeTEr2S6tzEkcFc421p6p4tlLy3stWk8rOUVsHoGD9ksHQ3EnUl77KE/"
      "t3yIU8ej3CrRntCbn/0fTiR7WkQ4kJa4UFHzrDK5ErbJ6/RlYP/R07NtwUxXF7iSrcg0zx/"
      "porBlmOtSup/"
      "D9DvO2HIzU52vtUnnlbl9QqjW7EZcRNj2AnCCX4pAnUAgeLqy2BmJmiYdReo47AfyvTt7VRu"
      "1Ce2DpMLPtD84NCxSGqzJt2QpcMGihSFpAmPewhe7uJM2hP9Ko00eXNYu7h/"
      "NQKtVf18YuMOdYXQc7UFeehfiLjUQjAK2OrGx76XqeSGDK7B+ZA1D10MuOASpIq4+"
      "qqcFMT6StCZWdRZ3qTDpKFBxsfVydNuxz0gV0wlhhlIjXIIoJ9LdwkSlvhLEgdJaWZcYtqcz"
      "Wsva9M3rJeURLLefxJewgSsBsitppTYYaoxgpRoQvnz6Z6dc3DbUZ5n6R5lFxssSMorV+"
      "T965uYCVoordt3K7lTOM85zeqBITE/"
      "bGLtzFGuMnzaEJnoKFJET0RZjgFyjQkvB+adNI9zA+"
      "uRivslUAX2P38Pvl4OIfnunkkZKdfDyTxY1FR4LiSX0LZ8w.";
  otrng_toolkit_assert(otrng_toolkit_parse_encoded_message(auth_r_msg));
}

void otrng_toolkit_test_parse_auth_i_message() {
  const char *auth_i_msg =
      "?OTR:AAQ3aS2Jvhyig/"
      "IFhoIvacC5tLMc9aDQI7YyKZeksJfGXDnn5oPKtRFjXD849oObOtn1aUXQ4xwHiZDQsEDyeC"
      "y2F5fgOHNyb7aJB3r0s5wwhUmKmN7ljOAGwoMs2lnsnMm98AeeQRpG7lW/"
      "PR9kqst4OIFD53QHRO8Ho99iIaLCBCes04o0MfaNwhPJmjmcDbFY/"
      "7bpGyNxlnENXaXW9vPXDGFoWDJta/smyutsrs3myiQfBo84lR1DMj0nex/"
      "IJJOOdS2hCqA+"
      "ANaNwF3sGXQ74PvymOvAamBql8b7oxurROzVhLsKBzxYLngxtSUeAUhu6giZyllljXcDjy3X"
      "cE9ZcoxRHyl4/83E8l1+wXeGhVx44U0npPMI/"
      "q4ptIOM8Z0vCGAxSUtPodJ2abepqYTdsAnSYAssngz+kTuj/"
      "XCXVU2z4Lo8boDQetfrP0LJjk6fJtKh9Mq08z8=.";
  otrng_toolkit_assert(otrng_toolkit_parse_encoded_message(auth_i_msg));
}

void otrng_toolkit_test_parse_non_int_auth_message() {
  const char *non_int_auth_msg =
      "?OTR:AAQNAAABAQAAAQIAAAAEAAEAAAEBAAIAECD4EBuCpR+GzGNKGKVGs+"
      "xbIe13ezSnY3BbwGna7Qh+"
      "Rg5llbkSf4iRnImFiV3ibkdhfw67Zvx5AAAEAAAAAzM0AAAFAAAAAFuNhrmJdf7HQnoi6G/"
      "f8XY/"
      "ZEPD7MahXXzZrxC4nv2QupZjkApWJvV+"
      "x909cwO560C0BhUEhC9qhRbjfIAPewhJaYVO6LibxhIUs45K1zBC7q8XdmGCE7ITybIgOYQl"
      "iTqajrOcbBJlg7EZJ6uthzKrvGUyFwA5xFq7pB8aeMJ7CwLwz34X8gPh1gFXnQaCCfAbx2jD"
      "N5+ZagnH0iOsD5+k04kDUR17lYynudWr5oAAAAGA/2sKr+9rTUiLh+/"
      "mHYEhdhoLB+QNHFhkyFvzGmE+F+D/vOKOXimrFlPT9ViVAX00q1SO5/"
      "94Jxz3F4A5SFUGWid3ZdWv571y6PEVS/"
      "zwLfs3lBFyN0zIjfTlLjnrjSAceaRF59rJTRxqcmGVe2m01WAOmsA6joa750hI8uTKgkn8KI"
      "COZUnj0Vq1f+cno0W4EE815WbdP4ChhZYTb0gamRG0VhedJTbjCkH6gz3vuyi+"
      "MZOqj0tWHKIJVADUCEGZbs0r4aGF6gP5/"
      "1Kypoftq7sX34OEcg99EFMBmlZd6cAc7a0rSzfu0G9Rvd7x4CljUB+ZcLkZERpqR5lRc+"
      "l71Kj3ItTa1Z3Y761qoPVeA9uMMHCPuMfCeemMDpvBJny0uUOJnmaP41RwvGfqYK80XNqwjm"
      "nVQlgYzSWWc4gpaDyhf/+b+ljx5z+AlLLlTvulSD5Pfgr4sSrgvaLziPFWDFivkAW/"
      "BVUmjrayC+4qDaPJH8l1GNM0l9DQVwsAJxAcV0/B4X/"
      "TJYVlu7eDpv4wdKnBUWRw1OYemIZm/"
      "8I2UKMugwC5soYtNyZNBkyUORTzFmbVNdkO5SjasAtXtHBiW1m+"
      "XrZ78sZCywICwBd51fxE6872PIcAbgOgqyUG/+LbUAxjPYn/"
      "aiHgn9N5gBnTPEuIUq52a7wu0LzYPySqj+8oGKxHVz+"
      "gcCzZ31WsmxwfCeESGRQtncyVWUBmiq+3mrWhxS/"
      "GMBYi7ftTVK4o0NWxIwlIZZVxYrKRLZGpLuD8l647dU1HfXwY2jgRGPW535do0rFBmD88DCF"
      "Pg/VYszLTzsh9GkcebjGX+ODW7AMAkg2qoMpndoS6/"
      "KgDbuC338joz4qSXH6rUYjW1vW7EkC5aiN67UicJ1IJKu5gLbgTYNAEgnKfwJIb1+"
      "IDb3wHvQbUt3QeNI26xD+MICt+aF/"
      "avuLksJmVHoUiZD+"
      "Dd5klof1IQf5KlJWrgGE3oi3J8jKmTApUHuGllLqA4EPIH0IcUQvg4ktdhTpu0MqCQv56D/"
      "hRQ7NmbAiqHU8rhTfCxqKhTeY=.";
  otrng_toolkit_assert(otrng_toolkit_parse_encoded_message(non_int_auth_msg));
}

void otrng_toolkit_test_parse_prekey_success_message() {
  const char *prekey_success_msg =
      "AAQGbQJzmFMujbgWDP1BjPZbsEO61+"
      "AmGPalm6QFnGugNXodeVM3MXxnMaWaLSxRkTfTPF3b+IDnuaOgnKIt8ckRvrjseEA=.";

  otrng_toolkit_assert(otrng_toolkit_parse_prekey_message(prekey_success_msg));
}

void otrng_toolkit_test_parse_prekey_failure_message() {
  const char *prekey_failure_msg =
      "AAQFbQJzmFMujbgWDP1BjPZbsEO61+"
      "AmGPalm6QFnGugNXodeVM3MXxnMaWaLSxRkTfTPF3b+IDnuaOgnKIt8ckRvrjseEA=.";

  otrng_toolkit_assert(otrng_toolkit_parse_prekey_message(prekey_failure_msg));
}

void otrng_toolkit_test_parse_prekey_storage_status_message() {
  const char *prekey_storage_status_msg =
      "AAQLbQJzmAAAAmRPS8JgMfNobrQ5n+8WIFQonbztNa3LBtd9AhJDaROm+lgX+"
      "Pmnpgp4Cn3riVPQqjbQgPl7S5I0CMqXqtLt31ZD.";

  otrng_toolkit_assert(
      otrng_toolkit_parse_prekey_message(prekey_storage_status_msg));
}

void otrng_toolkit_test_parse_prekey_dake_1_message() {
  const char *prekey_dake_1_msg =
      "AAQ1bQJzmAAAAAQAAW0Cc5gAAgAQZ++"
      "48mZmqGaQpCHm90ENOULrayINoV6l27eD2yDyqIyOr+Pe1FRVXil/"
      "Swz8EnZLQA+"
      "PTvoMxfuAAAQAAAADMzQAAAUAAAAAW53pEqRF0r7vPVC4du5DBAgTDYd06usVBhb3zzKyp0I"
      "/oy9wGmi29bEVIvapstcSKwQ4usAmW2iwXJ0mABEtlliXG9VqRtO7FBRJYVdOdFMgEjbfUxl"
      "a8i7k/"
      "yqWkNpXKQXmc8ZDVz6vYbGgGRD8ScilG4cxAGrdzziH1A0Oa2hVe+"
      "YfZTjOqWiTDpDJeKIEzkduptKe0DZD6blmx8D4jPIK2hdgvah2/UkbfInIAA==.";

  otrng_toolkit_assert(otrng_toolkit_parse_prekey_message(prekey_dake_1_msg));
}

void otrng_toolkit_test_parse_prekey_dake_2_message() {
  const char *prekey_dake_2_msg =
      "AAQ2bQJzmAAAABFwcmVrZXlzLmxvY2FsaG9zdAAQrC8mmPzxUoSAeFBbBBeR40JJ+"
      "wKa13H392zJMcy1LdsHAYqWsSjOm0HtipeiNtb06vTmtS0eCuSAx0FnKMhmQLtt5v33yaBLS"
      "KUkiPuZYHl3+K0m/"
      "hhEeilFFqU9Y0Tw7MtgZqFnXRGurcFhVTRR7wUAphHdgj0GOO0awTCEeevgWrXnG1xXU8OZV"
      "tcvTWbOhWIW58Uc+LGHuGuMZBoJslnFtTQnwvZloz86TRuoE75eBMqIo/"
      "coj2KI+AbKP95r3tf2vz8QgvWkYZrNg7IOWJ4ZHu9Tx/"
      "kztgbVy5CDm8KPKT0YmX8FYklnJGBgC1shYQzpuTuNnzAlVrLhA9T76hSXRXS6Q+"
      "Q7jfhisDtIKDmkxPGNaTaRoosl3jBVY8f+ydYZUiL+2MIbj820VBjVg6ukonm1lejgmqlR+"
      "c4yvAzgtjfa1IYqQLiBL/C/aBZnHxZ5B/4Ah2W/"
      "2QGuViXmrra560VfqZxM4yT8jetqcdzgvKgf1A8OOWdG87PYJ9VAPDXIOgCAAXNBJ9JNHdva"
      "2BxUe9ScKhs5zuKnuqaBX97syx+sip6vV3IZM3MIbrjyqt/gv37imoCHy0LTeFjamiUo.";

  otrng_toolkit_assert(otrng_toolkit_parse_prekey_message(prekey_dake_2_msg));
}

void otrng_toolkit_test_parse_prekey_dake_3_message() {
  const char *prekey_dake_3_msg =
      "AAQ3bQJzmPzxmOH8kx5a8yksIM60bZl5A5OJQWq4UeOiqg/"
      "64CeSRb+nnEWPjAJE9BT4z9AKrqDjgpoTKhUsFXw3KSO/"
      "X+ByzZ3+1AEo77toU+K5fLEWLnuK1vEBqmtxcFD3+"
      "hv0RvuW7rb0WdHuY1XCMBWoNCXgi0hBA44Xs/iVFZ/5JPORPTb2DGgMGxiv3/"
      "OV4ECVkL4urZCy/Rm16iSPypmrEaYOejq0Jz5rJADGmykowpJ2BYZdaQUgfEF/"
      "G2oOTGKunXHJMBIP2DVDVv++knuOqi7sRlhaatX+2gRqRroDaok2Wnw+vgPk4ui/"
      "AVCyOGiuz6+M/NbfWgD3FA1FbmNGH93aas4zfayMQowCPTHy1ytUw0tm+yeDwCVgt/"
      "nXYddZLwnEfWyYlMqDfI5bTCYdPpTrvmIX9jlIOQWkCOlTR84sH+tGBSN+"
      "VqTFcfV1mOF2IwAAAEMABAnzMunWnRDqawFFxFdcv0EjumsBW/"
      "i4xhuKh1uOJs6PaFrUpq588pbq5g+JNI4qhR6BXD1mJJp//kgT+hgM3PbI.";

  otrng_toolkit_assert(otrng_toolkit_parse_prekey_message(prekey_dake_3_msg));
}

void otrng_toolkit_test_parse_prekey_ensemble_retrieval_message() {
  const char *prekey_ensemble_retrieval_msg =
      "AAQTbQJzmAEAAAAEAAHboU/"
      "xAAIAEDu1PM1OQJLIocn85LEm901drrItkbYpFVuqkXSYFubxIywdVxDfFp4kirMCwUUHl7V"
      "k2onvnTKGgAAEAAAAAzM0AAAFAAAAAFud6QY0pWqatq6k+Dj34htqtvVX73GufWQ+"
      "lSqNf4Bkxu1bLU9FGdnEBh9H+iweU2cJ+zn6jqFRBNb4/"
      "IBD9+M77HtjUwn8u+UNyG0ZpNtutWvjelKmmbhi9bZvfeZMcTBpbEA089rRzc+qS1+"
      "UDgO55tTJEADboU/"
      "xAAAAAFuz4nMAESEVEvVVu+"
      "bTviqZZs2yxHiX152ZaHwIZvTGBlXCRWeQWnkg2l66xTC7yDXTxMqGSsPGTl8UgBLigFC7Nk"
      "0SKNgN0jjlNsxpTlVDk90seJ6lx5WB1l7xuAcsoUvfaBfh1O5Q6ypb5df9ulW7kQOvy4NkgG"
      "g8r9XzCH1RVeDuSdOIPlVJPUY/"
      "YAs7MyKsp24R63br5bCf5HfBcBf6ZERL6AxnjfobB10GQpA5AAAEDwNvVuvboU/"
      "xV5gUvC236JI8LsilpfPbsAv1Pzg40k7dXXBIKBrwLI/"
      "2nevn6NStaCjEESRjUN2TUKsOdkkqZyoAAAABgN7a7YnSlp7etkMlh1XeRCFCiBVHhjZEzhe"
      "+fqmHyTrDasSsdKr0cVfvsRboqeStUNTC4yi7lrLfKqsQnygQ+"
      "h1dE3d24SO00zg4prfnn0iUs9QWp1XsNVSWbWt1yNe5pRsp7g1mENi1h3odyHdl9m9icvldn"
      "H9EmyZKEiEkXi0K06Iqg0rYcHj3nATt3KdIM6KfjDLfWc3mISdeTL3Vq5sGZxV4SOsRzyhCh"
      "xblNz7otFd5lW1QYmHuPIc86SMu5OhczCyv0EGI2bYm9IlGtICesBSjYwrPI2u4PYHDXdCZi"
      "jCqdPz0vG+ggdbLSU545JigyL+hT9ITH+0eT8vDg1Kd2F36a5VOO9APEAklej/"
      "Vf7SG8IYMpyCJU7h5izzi5lCzu2tVc/"
      "9GN23Jr4Nn4MJAEQKSvCo9UiH2EQ2UpkUSGPZrUPW13pghHisuogPvmyXUk+5y+"
      "pxLvYW5CUwJ3CN7ykQyxOyGJe6VM1yX2mN2+Ov8NPAPnyes0ZFBydFpIg==.";

  otrng_toolkit_assert(
      otrng_toolkit_parse_prekey_message(prekey_ensemble_retrieval_msg));
}
