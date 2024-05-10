import {Component, OnInit} from '@angular/core';
import {UserService} from '../user.service';
import {User} from '../user';
import {Router, RouterLink} from '@angular/router';
import { FormsModule } from '@angular/forms';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-show-users',
  standalone: true,
  imports: [CommonModule, RouterLink, FormsModule],
  templateUrl: './show-users.component.html',
  styleUrls: ['./show-users.component.css']
})
export class ShowUsersComponent implements OnInit {

  users: Array<User> = [];
  role = '';
  name = '';

  constructor(private service: UserService, private router: Router) {}

  ngOnInit(): void {
    const previousRoleFilter = localStorage.getItem('roleFilter') ?? '';
    const previousNameFilter = localStorage.getItem('nameFilter') ?? '';
    this.role = previousRoleFilter;
    this.name = previousNameFilter;
    this.loadUsers(this.role, this.name);
  }

  loadUsers(role?: string, name?: string): void {
    this.service.fetchUsers(role, name).subscribe(users => {
      this.users = users;
    });
  }

  onFilter() {
    localStorage.setItem('roleFilter', this.role);
    localStorage.setItem('nameFilter', this.name);
    this.loadUsers(this.role, this.name);
  }
}
