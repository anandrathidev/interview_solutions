# -*- coding: utf-8 -*-
import cv2
import numpy as np
#from math import sqrt
#from alignment import alignImage
"""
The class that calculates the total rms of an image,
Assume opening an image with opencv2
transforms it into a matriz in wich each element represents the values of the colors blue, green and
red of each pixel, it returns the rms separated by color
axis for numpy
"""

theinput = ""

class ImgRMS:

  BLUE, GREEN, RED = tuple(range(3))
  ALONG_COL_AXIS, ALONG_ROW_AXIS, ALONG_CHANNEL_AXIS = tuple(range(3))

  def __init__(self, image):
    if len(image.shape)!=3:
      raise Exception( "This is not a correct image shape")
    if image.shape[2]!=3:
      raise Exception( "This image has incorrect channels (bgr)")
    self.image = image

  def _rms(self, image):
    """ inner helper rms function """
    return (image.astype('float64') - 128 )**2

  def _bgr_sqrt(self, total):
    """ inner helper to get bgr sqrt"""
    return (tuple(map(lambda x: np.sqrt(total[x]),
                      [ImgRMS.BLUE, ImgRMS.GREEN, ImgRMS.RED])))

  def rms(self, axis = ALONG_COL_AXIS):
    """ rms function that calculates the rms of an image separated
        by axis or total. axis can be row , column or None
    arguments:
      axis: ALONG_ROW_AXIS/ALONG_COL_AXIS/None
    Returns:
      tuple: best row/col , rms of blue, rms of green, rms of red
    """
    if not (axis == ImgRMS.ALONG_ROW_AXIS or
            axis == ImgRMS.ALONG_COL_AXIS or
            axis is None):
      raise Exception("valid axis values are ImgRMS.ALONG_ROW_AXIS,  \
                      ImgRMS.ALONG_COL_AXIS,  None")
    image = self._rms(self.image)
    total = np.mean(image,(ImgRMS.ALONG_ROW_AXIS,ImgRMS.ALONG_COL_AXIS,)) if (axis is None) else np.mean(image,axis=axis)

    if not axis is None:
      best_idx =  np.argmax(np.sum(total,(ImgRMS.ALONG_ROW_AXIS,)))
    return self._bgr_sqrt(total) if (axis is None) else \
      (best_idx,) + self._bgr_sqrt(total[best_idx])


# though not he best place to put unit test
# this should be in seperate file & test folder
import unittest
class Testrms(unittest.TestCase):

  def test_wrong_img_shape(self):
    # test with wrong image shape
    pix = np.array( [256,255,254] )
    row1 = np.array( [pix , pix+1 , pix+2] )
    with self.assertRaises(Exception):
     ImgRMS(row1)

  def test_incorrect_axis(self):
    # test with invalid axis
    pix = np.array( [256,255,254] )
    row1 = np.array( [pix , pix+1 , pix+2] )
    row2 = row1 + 1
    row3 = row1 + 2
    timg = np.array( [row1,row2,row3] )
    self.assertTupleEqual(timg.shape, (3,3,3), "shape mismatch")
    robg = ImgRMS(timg)
    with self.assertRaises(Exception):
      robg.rms(10)

  def test_rms_calculations(self):
    pix = np.array( [256,255,254] )
    row1 = np.array( [pix , pix+1 , pix+2] )
    row2 = row1 + 1
    row3 = row1 + 2
    timg = np.array( [row1,row2,row3] )
    self.assertTupleEqual(timg.shape, (3,3,3), "shape mismatch")
    robg = ImgRMS(timg)
    a = robg.rms(None)
    self.assertTupleEqual(a,(130.00512810398416, 129.00516785514188, 128.00520822737383) , "All RMS is wrong")
    c = robg.rms(ImgRMS.ALONG_COL_AXIS)
    self.assertTupleEqual(c,(2, 131.00254450455026, 130.0025640772776, 129.00258395344903) , "Col RMS is wrong")
    r = robg.rms(ImgRMS.ALONG_ROW_AXIS)
    self.assertTupleEqual(r,(2, 131.00254450455026, 130.0025640772776, 129.00258395344903) , "Row RMS is wrong")

  def test_rms_print(self):
    img1 = cv2.imread(theinput)
    robg = ImgRMS(img1)
    print( "Best Row" , robg.rms(ImgRMS.ALONG_ROW_AXIS) )
    print( "Best Col" , robg.rms(ImgRMS.ALONG_COL_AXIS) )
    print( "Best All" , robg.rms(None) )


def main():
  global theinput
  #theinput = "C:/Users/anand/Pictures/flag.PNG"
  theinput=str(input('full path of image file for RMS :'))
  unittest.main(exit=False, verbosity=4)

if __name__=="__main__":
    main()


"""
My Suggestion to Data
1. DRY = Dont Repeat Yourself
    "Every piece of knowledge must have a single, unambiguous, authoritative
    representation within a system".
    If you are repeating any code, then that goes into its own little function
    a. refactor code
    b. use method like map to apply same func on data
    example see  helper func
    _rms, _bgr_sqrt
    or bvroadcast see _bgr_sqrt and other numpy methods

    Here I saw that we all three functions are dooing prettymuch same
    thing and can be combined with parametyers to diffrenciate axis.

2. If possible think in OOPS and encapsulate code into a unit.
   [makes dynamic programming easyier instead of globals]
   You can take advantage of Encapsulation, Inheritance, Polymorphisim.

3. Prefer less lines of code is more readeable.
   e.g use single line if,
   avoid many variable defination by using them inline
   use broadcast instead of loops

4. Prefer numpy broadcast features to loop iteration.
   easy to read the code
   to parrelize may be in future interoperable with numba

5. PEP 8 -- Style Guide for Python Code https://www.python.org/dev/peps/pep-0008/
   Naming & spacing guidlines
   variable names, functions use snake case
   class names use camel case

6. Instead od using MAGIC numbers like 0,1,2 for axis etc
   define named MAGIC variables
   e.g
   ALONG_ROW_AXIS=1
   ALONG_COL_AXIS=0
   ALONG_CHANNEL_AXIS=2
   BLUE,GREEN,RED = 0,1,2

7. check input arguments in functions/constructor
   use @beartype / @enforce if possible for parameters type enforcement

8. General advice:
   prefer Generators over lists etc see itertools,

8. Always have unit test. it saves life :)

"""
