//------------------------------------------------------------------------------------
// Copyright (c) 2014 Dilshan R Jayakody. [jayakody2000lk@gmail.com]
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//------------------------------------------------------------------------------------

program rdrandliblazarus;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes, SysUtils, CustApp, rdrandlib;

const
  randomNumberCount = 20;

type
  TRandomBuffer = array [0..(randomNumberCount - 1)] of Cardinal;
  TRdRandLibLazarus = class(TCustomApplication)
  protected
    procedure DoRun; override;
  public
    constructor Create(TheOwner: TComponent); override;
  end;

procedure TRdRandLibLazarus.DoRun;
var
  ErrorMsg: String;
  randomResult : Byte;
  scanPos : Integer;
  randomBuffer: TRandomBuffer;
begin

  randomResult := GenerateRandomSet(randomNumberCount, @randomBuffer);

  if(randomResult = RDRAND_SUPPORT)then
  begin
    Writeln('RDRAND support is available.');
    for scanPos := 0 to (randomNumberCount - 1) do
    begin
      Writeln(' ' + IntToStr(randomBuffer[scanPos]));
    end;
  end
  else
  begin
    Writeln('RDRAND support is not available.');
  end;

  Writeln('');
  Writeln('Press <ENTER> to close this application...');
  Readln;
  Terminate;
end;

constructor TRdRandLibLazarus.Create(TheOwner: TComponent);
begin
  inherited Create(TheOwner);
  StopOnException:=True;
end;

var
  Application: TRdRandLibLazarus;
begin
  Application:=TRdRandLibLazarus.Create(nil);
  Application.Title:='RdrandlibLazarus';
  Application.Run;
  Application.Free;
end.

