'
'	@title
'		maskedkitty
'	@author
'		AHXR (https://github.com/AHXR)
'	@copyright
'		2018

'   maskedkitty is free software: you can redistribute it And/Or modify
'	it under the terms Of the GNU General Public License As published by
'	the Free Software Foundation, either version 3 Of the License, Or
'	(at your option) any later version.

'	maskedkitty is distributed In the hope that it will be useful,
'   but WITHOUT ANY WARRANTY; without even the implied warranty of
'   MERCHANTABILITY Or FITNESS FOR A PARTICULAR PURPOSE.  See the
'	GNU General Public License For more details.

'	You should have received a copy Of the GNU General Public License
'	along with maskedkitty. If Not, see < http: //www.gnu.org/licenses/>.
'
'=======================================================
Module main

    Sub Main(ByVal args() As String)
        '  args(0) - Path
        '  args(1) - Icon
        If My.Application.CommandLineArgs.Count = 2 Then
            IconInjector.InjectIcon(My.Application.CommandLineArgs(0), My.Application.CommandLineArgs(1))
        End If
    End Sub
End Module
