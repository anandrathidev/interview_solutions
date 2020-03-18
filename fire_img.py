# -*- coding: utf-8 -*-
"""
Created on Tue Mar 17 22:08:41 2020

@author: anandrathi
"""
import cv2
import numpy as np
from math import sqrt
#from alignment import alignImage

#the function that calculates the total rms of an image, since opening an image with opencv2
#transforms it into a matriz in wich each element represents the values of the colors blue, green and
#red of each pixel, it returns the rms separated by color

#axis for numpy

class ImgRMS:
  ALONG_ROW_AXIS=1
  ALONG_COL_AXIS=0
  ALONG_CHANNEL_AXIS=2
  BLUE,GREEN,RED = 0,1,2
  def __init__(self, image):
    self.image = image

  def _rms(self, image):
    return (image.astype('float64') - 128 )**2

  def _bgr_sqrt(self, total):
    blue_total = np.sqrt(total[ImgRMS.BLUE]).item()
    green_total = np.sqrt(total[ImgRMS.GREEN]).item()
    red_total = np.sqrt(total[ImgRMS.RED]).item()
    return (blue_total, green_total, red_total)

  def rms(self, axis = None):
    """ rms
        function that calculates the rms of an image separated
        by axis row = /column = ImgRMS.ALONG_COL_AXIS
        it returns a rms separated by color.

    Returns:
        tuple: best row/col , rms of blue, rms of green, rms of red
    """
    image=self.image
    rows,columns,channels = image.shape
    image = self._rms(image)
    #Sum along rows, cols for each channels
    total = np.mean(image,(ImgRMS.ALONG_ROW_AXIS,ImgRMS.ALONG_COL_AXIS,))  if (axis is None) else np.mean(image,axis=axis)
    #Sum along rows (now rows previously cols)
    if not axis is None:
      bestColIdx =  np.argmax(np.sum(total,(ImgRMS.ALONG_ROW_AXIS,)))
    return self._bgr_sqrt(total) if (axis is None) else (bestColIdx,) + self._bgr_sqrt(total[bestColIdx])

theinput = "C:/Users/anand/Pictures/flag.PNG"
img1 = cv2.imread(theinput)
robg = ImgRMS(img1)
print( robg.rms(ImgRMS.ALONG_ROW_AXIS) )
print( robg.rms(ImgRMS.ALONG_COL_AXIS) )
print( robg.rms(None) )
