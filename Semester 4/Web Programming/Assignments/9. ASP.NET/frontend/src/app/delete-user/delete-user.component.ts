import {Component, OnInit} from '@angular/core';
import {UserService} from '../user.service';
import {ActivatedRoute, Router, RouterLink} from '@angular/router';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-delete-user',
  standalone: true,
  imports: [CommonModule, RouterLink],
  templateUrl: './delete-user.component.html',
  styleUrls: ['./delete-user.component.css']
})
export class DeleteUserComponent implements OnInit {
  id: string = ' ';

  constructor(private service: UserService, private router: Router, private route: ActivatedRoute) {
  }

  ngOnInit(): void {
    this.route.queryParams.subscribe(params => {
      this.id = params['id']; 
    });
  }

  onYes(): void {
    if (this.id !== null) {
      this.service.deleteUser(this.id).subscribe(() => {
        this.router.navigate(['/users']).then(_ => {
          console.log('User deleted successfully');
        });
      });
    }
  }

}
