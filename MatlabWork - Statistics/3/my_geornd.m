## Copyright (C) 2019 Manuel
## 
## This program is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see
## <https://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## @deftypefn {} {@var{retval} =} my_geornd (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: Manuel <Manuel@DESKTOP-BBIUALQ>
## Created: 2019-10-30

function out = my_geornd(p,m)
  out = zeros(1,m);
  for i=1:m
    while ~first(p,1,1)
      out(i) += 1;
    endwhile
  endfor
endfunction
