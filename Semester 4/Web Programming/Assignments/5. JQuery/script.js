$(document).ready(function() {
    $('.desktop').css('top', '100%');
    $('.desktop:first').css('top', '0');
    $('.desktop').click(function() {
        var current = $(this);
        var next = $(this).next('.desktop');
        if (next.length == 0) {
            next = $('.desktop:first');
            $('.desktop').css('top', '100%');
            $('.desktop:first').css('top', '0');
        }
        current.animate({top: '-100%'}, 500, function() {
            setTimeout(function() {
                if (next.is($('.desktop:first'))) {
                    current.css('top', '100%');
                }
            }, 700);
        });
        next.css('top', '-100%').animate({top: '0'}, 500);
    });
});