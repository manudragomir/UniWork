## Copyright (C) 2019 Manuel
## 
## This program is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
## 0.2,
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see
## <https://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## @deftypefn {} {@var{retval} =} my_binord (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: Manuel <Manuel@DESKTOP-BBIUALQ>
## Created: 2019-10-30

function out = my_binord(p,n,m)
  aux = first(p,n,m);
  out = sum(aux,1);
endfunction
