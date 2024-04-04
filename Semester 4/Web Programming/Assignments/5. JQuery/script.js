$(document).ready(function() {
    $(this).scrollTop(0);
    $('.desktop').click(function() {
        var next = $(this).next('.desktop');
        if (next.length == 0) {
            next = $('.desktop:first');
        }
        $(this).animate({top: '100%'}, 500);
        next.animate({top: '0'}, 500);
    });
});
  