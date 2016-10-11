# Hello, world!
#
# This is an example function named 'hello'
# which prints 'Hello, world!'.
#
# You can learn more about package authoring with RStudio at:
#
#   http://r-pkgs.had.co.nz/
#
# Some useful keyboard shortcuts for package authoring:
#
#   Build and Reload Package:  'Cmd + Shift + B'
#   Check Package:             'Cmd + Shift + E'
#   Test Package:              'Cmd + Shift + T'

hello <- function() {
  print("Hello, world!")
}

read.ics<-function(file='/Users/danielfurth/Downloads/libics-1.5.2/test/testim.ics'){
  output<-.Call("readICS", file)


  maximum<-max(cumsum(output$histo[1:2047]))
  plot(seq(output$range[1], output$range[2], length.out=2047), cumsum(output$histo[1:2047]), type='l', xlim=c(0, 500), col=rgb(0,1,0,0.1),  ylab='Percentile', xlab='Intensity', axes=FALSE)
  axis(1)
  axis(2, at=c(0,maximum*0.5,maximum), labels=c(0,0.5,1), las=1)

  start<-seq(1, length(output$range), by=2)
  for(q in 2:15){
  lines(seq(output$range[start[q]], output$range[start[q]+1], length.out=2047), cumsum(output$histo[1:2047+2047*(q-1)]), col=rgb(0,1,0,0.2))
  }
  for(q in 16:30){
    lines(seq(output$range[start[q]], output$range[start[q]+1], length.out=2047), cumsum(output$histo[1:2047+2047*(q-1)]), col=rgb(1,0,1,0.2))
  }
  for(q in 31:(31+14)){
    lines(seq(output$range[start[q]], output$range[start[q]+1], length.out=2047), cumsum(output$histo[1:2047+2047*(q-1)]), col=rgb(1,0,0,0.2))
  }

  for(q in 45:(45+14)){
    lines(seq(output$range[start[q]], output$range[start[q]+1], length.out=2047), cumsum(output$histo[1:2047+2047*(q-1)]), col=rgb(0,1,1,0.2))
  }
  return(output)
}
